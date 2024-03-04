/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 21:23:57 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/04 12:59:59 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

static char	*create_sem_name(int id);

void	run_process(t_table *table)
{
	pid_t	p_id;
	int		i;

	i = 0;
	table->start = gettime(MILLISEC);
	while (i++ < table->ph_nb)
	{
		p_id = fork();
		if (!p_id)
			start_routine(table, i);
		else if (p_id == -1)
			error_exit("FORK_ERROR");
	}
	p_id = waitpid(0, NULL, 0);
	while (p_id != -1)
		p_id = waitpid(0, NULL, 0);
}

void	start_routine(t_table *table, int id)
{
	set_philo(table, id);
	sleep_even(table);
	if (pthread_create(&table->monitor, NULL, &monitor_death, table))
	{
		clean (table);
		error_exit("THREAD ERROR");
	}
	while (true)
	{
		if (eat(table) || should_stop(get_philo_state(table)))
			break ;
		if (ft_sleep(table) || should_stop(get_philo_state(table)))
			break ;
		if (print_msg(table, "is thinking"))
			break ;
	}
	if (pthread_join(table->monitor, NULL))
		exit(EXIT_FAILURE);
	sem_close(table->philo.philo_sem);
	exit (0);
}

void	set_philo(t_table *table, int id)
{
	char	*sem_name;

	sem_name = create_sem_name(id);
	if (!sem_name)
	{
		free(sem_name);
		clean (table);
		error_exit("MALLOC ERROR");
	}
	sem_unlink(sem_name);
	table->philo.philo_sem = sem_open(sem_name, O_CREAT, 0644, 1);
	sem_unlink(sem_name);
	free(sem_name);
	table->philo.id = id;
	last_meal_update(table);
}

static char	*create_sem_name(int id)
{
	return (ft_strmerge(ft_strdup("philo_"), ft_itoa(id)));
}
