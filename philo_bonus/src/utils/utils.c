/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:11:06 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/11 01:21:24 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Exits the program with an error message.
 *
 * This function prints an error message in red color and exits the program
 * with failure status.
 *
 * @param message The error message to be displayed.
 */
void	error_exit(const char *message)
{
	printf(RED"%s"RST"\n", message);
	exit (EXIT_FAILURE);
}

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
