/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:34:27 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/06 17:36:36 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static bool	philo_died(t_philo *ph);

/**
 * @brief Monitors the dining philosophers and detects if any philosopher has
 * died.
 *
 * This function monitors the dining philosophers and checks if any philosopher
 * has died.
 * It waits for all threads to start running, then continuously checks the
 * status of each philosopher.
 * If a philosopher is found to have died, it writes the appropriate status and
 * marks the end of the simulation.
 *
 * @param data A pointer to the table structure containing information about the
 * dining philosophers.
 * @return NULL
 */
void	*monitor(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!threads_running(table->table_mtx, &table->th_nbr, table->ph_nb))
		;
	while (!simulation_status(table))
	{
		i = -1;
		while (++i < table->ph_nb && !simulation_status(table))
		{
			if (philo_died(table->philo + i))
			{
				write_status(DIED, table->philo + i, DEBUG_MODE);
				set_bool(table->table_mtx, &table->end, true);
			}
		}
	}
	return (NULL);
}

/**
 * @brief Checks if a philosopher has died.
 *
 * This function checks if a philosopher has died by calculating the time
 * elapsed since their last meal
 * and comparing it with the time allowed to pass before a philosopher is
 * considered to have died.
 *
 * @param ph A pointer to the philosopher structure to be checked.
 * @return true if the philosopher has died, false otherwise.
 */
static bool	philo_died(t_philo *ph)
{
	long	elapsed;
	long	t_to_die;

	if (get_bool(ph->philo_mtx, &ph->full))
		return (false);
	elapsed = gettime(MILLISEC) - get_long(ph->philo_mtx, &ph->last_meal);
	t_to_die = ph->table->die / 1e3;
	if (elapsed > t_to_die)
		return (true);
	return (false);
}
