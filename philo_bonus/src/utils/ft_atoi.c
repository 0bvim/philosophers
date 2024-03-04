/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:59:35 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/04 19:47:31 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Converts a string to a long integer recursively.
 *
 * This function recursively converts a string to a long integer. It handles
 * sign, ignores leading whitespaces, and returns the result.
 *
 * @param string The string to be converted.
 * @param sign The sign of the number.
 * @param nb The current value of the number being built.
 * @return The converted long integer value.
 */
static long	ft_atoi_recursive(const char *string, long sign, long nb)
{
	if (*string == '\0')
		return (nb * sign);
	if (*string == '-' || *string == '+')
	{
		if (*(string + 1) == '-' || *(string + 1) == '+')
			return (0);
		if (*string == '-')
			sign = -1;
		return (ft_atoi_recursive(string + 1, sign, nb));
	}
	if (*string >= '0' && *string <= '9')
	{
		nb = (nb * 10) + (*string - '0');
		return (ft_atoi_recursive(string + 1, sign, nb));
	}
	return (nb * sign);
}

/**
 * @brief Converts a string to a long integer.
 *
 * This function converts a string to a long integer using recursion.
 *
 * @param nptr The string to be converted.
 * @return The converted long integer value.
 */
long	ft_atol(const char *nptr)
{
	return (ft_atoi_recursive(nptr, 1, 0));
}
