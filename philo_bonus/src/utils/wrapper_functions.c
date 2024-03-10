/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:46:26 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/09 23:22:54 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
