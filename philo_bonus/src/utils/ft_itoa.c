/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:41:41 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/06 15:45:10 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


static int	ft_feedback(int *count, int n)
{
	if (n < 0)
		return (*count += 1, -1);
	return (1);
}

static char	*ft_str_len(unsigned int n, int *count)
{
	char	*str;

	if (n >= 10)
	{
		*count += 1;
		str = ft_str_len(n / 10, count);
	}
	else
		str = (char *)malloc((*count + 1) * sizeof(char));
	if (!str)
		return (0);
	return (str);
}

static void	ft_recursive_itoa(unsigned int n, int count, char *str)
{
	if (n >= 10)
		ft_recursive_itoa(n / 10, count - 1, str);
	str[count] = (n % 10) + '0';
}

char	*ft_itoa(int n)
{
	int		count;
	int		signal;
	char	*str;

	count = 1;
	signal = ft_feedback(&count, n);
	str = ft_str_len(n * signal, &count);
	if (!str)
		return (NULL);
	if (signal == -1)
		str[0] = '-';
	ft_recursive_itoa(n * signal, count - 1, str);
	return (str);
}
