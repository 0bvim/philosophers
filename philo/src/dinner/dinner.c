/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:18:44 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/29 12:42:32 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->max_meals)
		return ;
	else if (1 == table->ph_nb)
		;//TODO
	else
	{
		while (++i < table->ph_nb)
		{
			safe_thread_handle(&table->philo[i].th_id, dinner_simulation,
				&table->philo[i], CREATE);
		}
	}
	table->start = gettime(MILLISEC);
	set_bool(&table->table_mtx, &table->all_up, true);
	i = -1;
	while (++i < table->ph_nb)
		safe_thread_handle(&table->philo[i].th_id, NULL, NULL, JOIN);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while (simulation_status(philo->table))
	{
		if (philo->full)
			break ;
		write_status(SLEEPING, philo, DEBUG_MODE);
	}
	return (NULL);
}
