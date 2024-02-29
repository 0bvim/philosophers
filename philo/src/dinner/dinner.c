/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:18:44 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/29 12:59:14 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	eat(t_philo *philo);

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
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->sleep, philo->table);
	}
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mtx_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mtx_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISEC));
	philo->meals++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->eat, philo->table);

}
