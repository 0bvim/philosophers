/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:18:44 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/02 13:03:31 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

static void	eat(t_philo *philo);

/**
 * @brief Starts the dinner simulation on the specified table.
 *
 * This function starts the dinner simulation on the specified table by
 * creating threads for each philosopher and a monitor thread.
 * It sets the start time of the simulation, ensures all philosophers
 * are ready to start, waits for all philosopher threads and
 * the monitor thread to finish, and then marks the end of the simulation.
 *
 * @param table A pointer to the table structure containing information
 * about the dining philosophers and their state.
 */
void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->max_meals)
		return ;
	else if (1 == table->ph_nb)
		safe_thread_handle(&table->philo[0].th_id, lonely_day,
			&table->philo[0], CREATE);
	else
		while (++i < table->ph_nb)
			safe_thread_handle(&table->philo[i].th_id, dinner_simulation,
				&table->philo[i], CREATE);
	safe_thread_handle(&table->monitor, monitor, table, CREATE);
	table->start = gettime(MILLISEC);
	set_bool(&table->table_mtx, &table->all_up, true);
	i = -1;
	while (++i < table->ph_nb)
		safe_thread_handle(&table->philo[i].th_id, NULL, NULL, JOIN);
	set_bool(&table->table_mtx, &table->end, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}

/**
 * @brief Simulates a philosopher's behavior during the dinner.
 *
 * This function simulates a philosopher's behavior during the dinner.
 * It waits for all threads to be ready, records the last meal time,
 * increases the number of threads at the table, unsynchronizes philosophers,
 * enters a loop to simulate eating, sleeping, and thinking, and exits the loop
 * when the simulation status indicates it's time to end or the philosopher
 * is full.
 *
 * @param data A pointer to the philosopher structure containing information
 * about the philosopher and the table they are dining at.
 * @return NULL
 */
void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISEC));
	increase_long(&philo->table->table_mtx, &philo->table->th_nbr);
	unsync_philos(philo);
	while (!simulation_status(philo->table))
	{
		if (get_bool(&philo->philo_mtx, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

/**
 * @brief Simulates a philosopher eating.
 *
 * This function simulates a philosopher eating by locking the first and second
 * forks, recording the time of the last meal, increasing the number of meals
 * eaten by the philosopher, indicating the philosopher is eating, sleeping for
 * the duration of eating time, and unlocking the forks when done. If the
 * maximum number of meals is reached, it marks the philosopher as full.
 *
 * @param philo A pointer to the philosopher structure containing information
 * about the philosopher and the table they are dining at.
 */
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
	if (philo->table->max_meals > 0 && philo->meals == philo->table->max_meals)
		set_bool(&philo->philo_mtx, &philo->full, true);
	safe_mtx_handle(&philo->first_fork->fork, UNLOCK);
	safe_mtx_handle(&philo->second_fork->fork, UNLOCK);
}

/**
 * @brief Simulates a philosopher thinking.
 *
 * This function simulates a philosopher thinking by calculating the time to
 * think based on the eating and sleeping times. If it's not a pre-simulation
 * thinking, it writes the thinking status to the output. If the number of
 * philosophers is even, the function returns early since it doesn't
 * need to think. Otherwise, it calculates the time to think based on the time
 * to eat and sleep, and sleeps for that duration.
 *
 * @param philo A pointer to the philosopher structure containing information
 * about the philosopher and the table they are dining at.
 * @param pre_simulation A boolean indicating whether it's a pre-simulation
 * thinking.
 */
void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->ph_nb % 2 == 0)
		return ;
	t_eat = philo->table->eat;
	t_sleep = philo->table->sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

/**
 * @brief Simulates a lonely philosopher's day.
 *
 * This function simulates a lonely philosopher's day by waiting for all
 * threads to be ready, recording the time of the last meal, increasing the
 * number of threads at the table, and then entering a loop to wait for the
 * simulation to end.
 *
 * @param arg A pointer to the philosopher structure containing information
 * about the philosopher and the table they are dining at.
 * @return NULL
 */
void	*lonely_day(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISEC));
	increase_long(&philo->table->table_mtx, &philo->table->th_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_status(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}
