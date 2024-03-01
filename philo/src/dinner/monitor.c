/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:34:27 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/01 19:22:47 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static bool	philo_died(t_philo *ph);

void	*monitor(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!threads_running(&table->table_mtx, &table->th_nbr, table->ph_nb))
		;
	while (!simulation_status(table))
	{
		i = -1;
		while (++i < table->ph_nb && !simulation_status(table))
		{
			if (philo_died(table->philo + i))
			{
				set_bool(&table->table_mtx, &table->end, true);
				write_status(DIED, table->philo, DEBUG_MODE);
			}
		}
	}
	return (NULL);
}

static bool	philo_died(t_philo *ph)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(&ph->philo_mtx, &ph->full))
		return (false);
	elapsed = gettime(MILLISEC) - get_long(&ph->philo_mtx, &ph->last_meal);
	t_to_die = ph->table->die;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}
