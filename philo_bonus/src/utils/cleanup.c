/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:38:01 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/09 22:38:08 by vde-frei         ###   ########.fr       */
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
	if (table->philo)
	{
		i = -1;
		while (++i < table->ph_nb)
		{
			make_semaphore_name(SEM_PHILO, (char*)semaphore, i);
			sem_unlink(semaphore);
			make_semaphore_name(SEM_PHILOEAT, (char*)semaphore, i);
			sem_unlink(semaphore);
		}
		free(table->philo);
	}
}
