/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:16:01 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/01 12:41:16 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/*
 * @brief Wait all threads to syncronize.
 * @param mtx Mutex variable to verified.
 * @param value Value to get.
 * @return Does not return.
 **/
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_up))
		;
}

void	increase_long(t_mtx *mutex, long *value)
{
	safe_mtx_handle(mutex, LOCK);
	(*value)++;
	safe_mtx_handle(mutex, UNLOCK);
}

void	unsync_philos(t_philo *philo)
{
	if (philo->table->ph_nb % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->table);
	}
	else
	{
		if (philo->id % 2)
			thinking(philo, true);
	}
}
