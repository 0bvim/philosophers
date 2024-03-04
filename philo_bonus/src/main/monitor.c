/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:09:43 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/03 22:48:50 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	should_stop(t_philo_status state);

void	*monitor_death(void *data_p)
{
	t_table	*table;

	table = (t_table *)data_p;
	while (should_stop(get_philo_state(table)) == false)
	{
		if (someone_died())
			return (set_philo_state(table, FINISH), NULL);
		if (philo_died(table))
		{
			sem_wait(table->sem_print);
			if (philo_died(table) && someone_died() == false)
			{
				set_philo_state(table, DEAD);
				let_others_know();
				printf("%ld %d %s\n", gettime(MILLISEC) - table->start,
					table->philo.id, "died");
				sem_post(table->sem_print);
				break ;
			}
			sem_post(table->sem_print);
		}
		usleep(1000);
	}
	return (NULL);
}

static bool	should_stop(t_philo_status state)
{
	if (state == DEAD || state == FINISH || state == FULL)
		return (true);
	return (false);
}

bool	someone_died(void)
{
	sem_t	*death;
	death = sem_open("/death", AT_EACCESS, 0);
	if (death == SEM_FAILED)
		return (false);
	sem_close(death);
	return (true);
}

void	let_others_know(void)
{
	sem_open("/death", O_CREAT, 0644, 0);
}
