/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:38:01 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/10 00:56:38 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

void	clean(t_table *table)
{
	int		i;
	char	semaphore[255];

	sem_unlink(SEM_FORK);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_DEADW);
	sem_close(table->fork_mtx);
	sem_close(table->write_mtx);
	sem_close(table->dead_write_mtx);
	sem_close(table->have_died_mtx);
	if (table->philo)
	{
		i = -1;
		while (++i < table->ph_nb)
		{
			sem_close(table->philo[i].mutex);
			sem_close(table->philo[i].eat_count_mtx);
			make_semaphore_name(SEM_PHILO, (char*)semaphore, i);
			sem_unlink(semaphore);
			make_semaphore_name(SEM_PHILOEAT, (char*)semaphore, i);
			sem_unlink(semaphore);
		}
		free(table->philo);
	}
}
