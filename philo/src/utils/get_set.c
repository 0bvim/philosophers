/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 00:55:56 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/28 01:30:40 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/*
 * @brief function to set value of mutex for philo and fork
 * @param mtx Mutex variable to lock and unlock.
 * @param dst Destination of value to be set.
 * @param value Value to be set.
 * @return Does not return.
 **/
void	set_bool(t_mtx *mtx, bool *dst, bool value)
{
	safe_mtx_handle(mtx, LOCK);
	*dst = value;
	safe_mtx_handle(mtx, UNLOCK);
}

/*
 * @brief function to get value of mutex for philo and fork.
 * @param mtx Mutex variable to lock and unlock.
 * @param value Value to get.
 * @return The value.
 **/
bool	get_bool(t_mtx *mtx, bool *value)
{
	bool	ret;

	safe_mtx_handle(mtx, LOCK);
	ret = *value;
	safe_mtx_handle(mtx, UNLOCK);
	return (ret);
}

/*
 * @brief function to set value of mutex for eat, sleep and die.
 * @param mtx Mutex variable to lock and unlock.
 * @param dst Destination of value to be set.
 * @param value Value to be set.
 * @return Does not return.
 **/
void	set_long(t_mtx *mtx, long *dst, long value)
{
	safe_mtx_handle(mtx, LOCK);
	*dst = value;
	safe_mtx_handle(mtx, UNLOCK);
}

/*
 * @brief function to get value of mutex for eat, sleep and die.
 * @param mtx Mutex variable to lock and unlock.
 * @param value Value to get.
 * @return The value.
 **/
long	get_long(t_mtx *mtx, long *value)
{
	long	ret;

	safe_mtx_handle(mtx, LOCK);
	ret = *value;
	safe_mtx_handle(mtx, UNLOCK);
	return (ret);
}
