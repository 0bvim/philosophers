/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:16:01 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/06 16:27:14 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

/**
 * @brief Waits for all threads to be ready.
 *
 * This function waits until all threads are ready by checking the boolean flag
 * indicating whether all threads are up.
 *
 * @param table A pointer to the table structure containing information about
 *              the dining philosophers.
 */
void	wait_all_threads(t_table *table)
{
	while (!get_bool(table->table_mtx, &table->all_up))
		;
}

/**
 * @brief Increases a long integer value while safely handling mutex locks.
 * 
 * This function increases a long integer value while safely handling mutex locks
 * to ensure thread safety.
 * 
 * @param mutex A pointer to the mutex structure used for synchronization.
 * @param value A pointer to the long integer value to be increased.
 */
void	increase_long(sem_t *mutex, long *value)
{
	sem_wait(mutex);
	(*value)++;
	sem_post(mutex);
}

/**
 * @brief Unsynchronizes philosophers based on the number of philosophers.
 * 
 * This function unsynchronizes philosophers based on the number of philosophers
 * at the table. If the number of philosophers is even, it introduces a delay for
 * even-numbered philosophers. If the number of philosophers is odd, it triggers
 * pre-simulation thinking for odd-numbered philosophers.
 * 
 * @param philo A pointer to the philosopher structure to be unsynchronized.
 */
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

/**
 * @brief Checks if all threads are running.
 * 
 * This function checks if all threads are running by comparing the number of
 * running threads with the total number of threads expected.
 * 
 * @param mtx A pointer to the mutex structure used for synchronization.
 * @param threads A pointer to the long integer value representing the number of
 *                running threads.
 * @param ph_nb The total number of threads expected to run.
 * @return true if all threads are running, false otherwise.
 */
bool	threads_running(t_mtx *mtx, long *threads, long ph_nb)
{
	bool	ret;

	ret = false;
	safe_mtx_handle(mtx, LOCK);
	if (*threads == ph_nb)
		ret = true;
	safe_mtx_handle(mtx, UNLOCK);
	return (ret);
}
