/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:46:26 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/29 10:30:53 by vde-frei         ###   ########.fr       */
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
 * @brief Function to verify errors about thread.
 * @param status Return status of functions <CREATE> <JOIN> DETACH>.
 * @param opcode Code defined in enum for operations.
 * @return This function does not return.
 */
static void	handle_thread_error(int status, t_code opcode)
{
	if (0 == status)
		return ;
	if (EAGAIN == status)
		error_exit("No resources to create another thread");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate permission");
	else if (EINVAL == status && CREATE == opcode)
		error_exit("Invalid value specified by attr.");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The value is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be found");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected.");
}

/**
 * @brief Function to handle threads
 * @param thread Thread to be handled.
 * @param *(*foo) Function pointer of routine.
 * @param Data Struct with variables to operations.
 * @param opcode Operation code of action.
 * @return This function does not return.
 */
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_code opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit ("Wrong operation code. Use: <CREATE> <JOIN> <DETACH>");
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
	else if (EINVAL == status && INIT == opcode)
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
