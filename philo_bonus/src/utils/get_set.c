/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:55:56 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/06 17:20:05 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

/**
 * @brief Sets a boolean value with mutex locking.
 *
 * This function sets a boolean value with mutx locking to ensure thread safety.
 *
 * @param mtx A pointer to the mutex structure used for synchronization.
 * @param dst A pointer to the boolean value to be set.
 * @param value The value to set.
 */
void	set_bool(sem_t *mtx, bool *dst, bool value)
{
	safe_mtx_handle(mtx, LOCK, NULL);
	*dst = value;
	safe_mtx_handle(mtx, UNLOCK, NULL);
}

/**
 * @brief Retrieves a boolean value with mutex locking.
 *
 * This function retrieves a boolean value with mutex locking to ensure thread
 * safety.
 *
 * @param mtx A pointer to the mutex structure used for synchronization.
 * @param value A pointer to the boolean value to be retrieved.
 * @return The retrieved boolean value.
 */
bool	get_bool(sem_t *mtx, bool *value)
{
	bool	ret;

	sem_wait(mtx);
	ret = *value;
	sem_post(mtx);
	return (ret);
}

/**
 * @brief Sets a long integer value with mutex locking.
 *
 * This function sets a long integer value with mutex locking to ensure thread
 * safety.
 *
 * @param mtx A pointer to the mutex structure used for synchronization.
 * @param dst A pointer to the long integer value to be set.
 * @param value The value to set.
 */
void	set_long(sem_t *mtx, long *dst, long value)
{
	sem_wait(mtx);
	*dst = value;
	sem_post(mtx);
}

/**
 * @brief Retrieves a long integer value with mutex locking.
 *
 * This function retrieves a long integer value with mutex locking to ensure
 * thread safety.
 *
 * @param mtx A pointer to the mutex structure used for synchronization.
 * @param value A pointer to the long integer value to be retrieved.
 * @return The retrieved long integer value.
 */
long	get_long(sem_t *mtx, long *value)
{
	long	ret;

	sem_wait(mtx);
	ret = *value;
	sem_post(mtx);
	return (ret);
}

/**
 * @brief Checks the status of the simulation.
 *
 * This function checks the status of the simulation by retrieving the value of the end flag
 * from the table structure.
 *
 * @param table A pointer to the table structure containing information about the dining philosophers.
 * @return true if the simulation has ended, false otherwise.
 */
bool	simulation_status(t_table *table)
{
	return (get_bool(table->table_mtx, &table->end));
}
