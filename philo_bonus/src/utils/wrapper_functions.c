/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:46:26 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/02 13:03:13 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

/**
 * @brief Safely allocates memory.
 *
 * This function safely allocates memory using malloc and checks for allocation
 * errors.
 *
 * @param bytes The number of bytes to allocate.
 * @return A pointer to the allocated memory.
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
 * @brief Handles thread-related errors.
 * 
 * This function handles errors that may occur during thread creation, joining,
 * or detaching.
 * 
 * @param status The status code returned by the pthread function.
 * @param opcode The operation code indicating the type of operation.
 * (CREATE, JOIN, DETACH).
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
 * @brief Safely handles thread operations.
 *
 * This function safely handles thread operations such as creation,
 * joining, or detaching, and checks for errors.
 *
 * @param thread A pointer to the pthread_t variable.
 * @param foo The function pointer to the thread function.
 * @param data The data to be passed to the thread function.
 * @param opcode The operation code indicating the type of operation.
 * (CREATE, JOIN, DETACH).
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
 * @brief Handles mutex-related errors.
 *
 * This function handles errors that may occur during mutex initialization,
 * locking, unlocking, or destruction.
 *
 * @param status The status code returned by the pthread_mutex function.
 * @param opcode The operation code indicating the type of operation
 * (INIT, LOCK, UNLOCK, DESTROY).
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
 * @brief Safely handles mutex operations.
 *
 * This function safely handles mutex operations such as initialization,
 * locking, unlocking, or destruction, and checks for errors.
 *
 * @param mutex A pointer to the mutex variable.
 * @param opcode The operation code indicating the type of operation
 * (INIT, LOCK, UNLOCK, DESTROY).
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
