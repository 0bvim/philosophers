/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:18:44 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/29 10:28:53 by vde-frei         ###   ########.fr       */
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
	set_bool(&table->table_mtx, &table->all_up, true);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	return (NULL);
}
