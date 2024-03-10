/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:11:06 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/09 23:22:37 by vde-frei         ###   ########.fr       */
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
