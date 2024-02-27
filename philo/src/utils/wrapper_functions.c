/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:46:26 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/27 20:50:09 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief function to alloc memory safe.
 * @param bytes Size to be allocated.
 * @return Allocated content.
*/
void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (NULL == ret)
		error_exit("Memory allocation error.");
	return (ret);
}

/**
 * @brief Function to verify errors about mutex.
 * @param status Return status of functions.
 * @param opcode Code defined in enum for operations.
 * @return This function does not return.
 */
static void	handle_mtx_error(int status, t_code opcode)
{
	if (0 == status)
		return ;
	if (EINVAL == status
		&& (LOCK == opcode || UNLOCK == opcode || DESTROY == opcode))
		error_exit("Invalid value specified by mutex.");
	else if (EINVAL == status && INIT)
		error_exit("Invalid value specified by attr.");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur. Thread blocked waiting for mutex.");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		error_exit("Memory is not enough to create another mutex");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}

/**
* @brief Function to do a operation of mutex.
* @param mutex Variable to do operation.
* @param operation Enum code with the operation to be done.
* @return This function does not have a return value.
*/
void	safe_mtx_handle(t_mtx *mutex, t_code opcode)
{
	if (INIT == opcode)
		handle_mtx_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (LOCK == opcode)
		handle_mtx_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mtx_error(pthread_mutex_unlock(mutex), opcode);
	else if (DESTROY == opcode)
		handle_mtx_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Invalid operation code.");
}
