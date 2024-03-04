/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:55:56 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/02 03:24:27 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Sets a boolean value with mutex locking.
 *
 * This function sets a boolean value with mutx locking to ensure thread safety.
 *
 * @param mtx A pointer to the mutex structure used for synchronization.
 * @param dst A pointer to the boolean value to be set.
 * @param value The value to set.
 */
void	set_bool(t_mtx *mtx, bool *dst, bool value)
{
	safe_mtx_handle(mtx, LOCK);
	*dst = value;
	safe_mtx_handle(mtx, UNLOCK);
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
bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	safe_mtx_handle(mtx, LOCK);
	ret = *value;
	safe_mtx_handle(mtx, UNLOCK);
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
void	set_long(t_mtx *mtx, long *dst, long value)
{
	safe_mtx_handle(mtx, LOCK);
	*dst = value;
	safe_mtx_handle(mtx, UNLOCK);
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
long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	safe_mtx_handle(mtx, LOCK);
	ret = *value;
	safe_mtx_handle(mtx, UNLOCK);
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
	return (get_bool(&table->table_mtx, &table->end));
}
