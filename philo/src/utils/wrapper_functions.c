/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:46:26 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/27 19:18:29 by vde-frei         ###   ########.fr       */
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
	if (NULL = ret)
	{
		printf("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	return (ret);
}

/**
* @brief Function to do a operation of mutex.
* @param mutex Variable to do operation.
* @param operation Enum code with the operation to be done.
* @return This function does not have a return value.
*/
void	safe_mtx_handle(t_mtx *mutex, t_code operation)
{
	if (CREATE == operation)
		pthread_mutex_create(mutex);
	else if (INIT == operation)
		pthread_mutex_init(mutex);
	else if (LOCK == operation)
		pthread_mutex_lock(mutex);
	else if (UNLOCK == operation)
		pthread_mutex_unlock(mutex);
	else if (DESTROY == operation)
		pthread_mutex_destroy(mutex);
	else if (DETACH == operation)
		pthread_mutex_detach(mutex);
}
