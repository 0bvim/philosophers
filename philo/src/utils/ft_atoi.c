/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 12:59:35 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/27 18:28:05 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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

long	ft_atol(const char *nptr)
{
	return (ft_atoi_recursive(nptr, 1, 0));
}
