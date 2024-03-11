/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:37:20 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/11 02:04:07 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	start_process(t_table *table)
{
	int	i;

	table->start = get_time();
	i = -1;
	while (++i < table->ph_nb)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid < 0)
			return (true);
		else if (!table->philo[i].pid)
			routine(&table->philo[i]);
		usleep(100);
	}
	return (false);
}

void	wait_and_finish(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->ph_nb)
		kill(table->philo[i++].pid, SIGKILL);
	clean(table);
}

bool	start_monitor(t_table *table)
{
	pthread_t	tid;

	if (table->max_meals > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_count, (void *)table) != 0)
			return (true);
		pthread_detach(tid);
	}
	return (false);
}

void	star_and_run_program(t_table *table, char **av)
{
	parser_input(table, av);
	if (start_monitor(table) || start_process(table))
	{
		clean(table);
		error_exit("error: fatal\n");
	}
}
