/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:34:27 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/11 01:16:47 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_count(void * table_v)
{
	t_table *table;
	int		total;
	int		i;

	table = (t_table*)table_v;
	total = 0;
	while (total < table->max_meals)
	{
		i = 0;
		while (i < table->ph_nb)
			sem_wait(table->philo[i++].eat_count_mtx);
		total++;
	}
	display_message(&table->philo[0], FULL);
	sem_post(table->have_died_mtx);
	return ((void*)false);
}

void	*monitor(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo*)philo_v;
	while (true)
	{
		sem_wait(philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			display_message(philo, DIED);
			sem_post(philo->mutex);
			sem_post(philo->table->have_died_mtx);
			return ((void*)0);
		}
		sem_post(philo->mutex);
		usleep(100);
	}
	return ((void*)0);
}
