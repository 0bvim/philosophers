/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 00:19:21 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/29 12:13:28 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	print_helper(void);
static bool	arg_validation(int ac, char **av);
static bool	is_digit(char c);
static bool	check_range(char **av);

void	check(int ac, char **av)
{
	if ((5 == ac || 6 == ac) && arg_validation(ac, av))
		return ;
	print_helper();
	exit (EXIT_FAILURE);
}

static bool	arg_validation(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (!is_digit(av[i][j]))
				return (false);
			j++;
		}
	}
	return (check_range(av));
}

static bool	is_digit(char c)
{
	return (c >= 48 && c <= 57);
}

static bool	check_range(char **av)
{
	if (INT_MAX < ft_atol(av[1]))
		return (false);
	else if ((ft_atol(av[2]) * 1e3) < 6e4)
		return (false);
	else if ((ft_atol(av[3]) * 1e3) < 6e4)
		return (false);
	else if ((ft_atol(av[4]) * 1e3) < 6e4)
		return (false);
	else
		return (true);
}

static void	print_helper(void)
{
	printf(MAG"Instructions to execute:"RST"\n");
	printf("1st arg: "YLW"Number of Philoshophers"RST"\n");
	printf("2nd arg: "CYA"time to "RST RED"die"RST"\n");
	printf("3nd arg: "CYA"time to "RST ORG"eat"RST"\n");
	printf("4th arg: "CYA"time to "RST BLU"sleep"RST"\n");
	printf("5th arg: "CYA"number of times each must eat. (opt)"RST"\n");
	printf("Example 4 args: "LRED"./philo 5 800 200 200"RST"\n");
	printf("Example 5 args: "LRED"./philo 5 800 200 200 7"RST"\n");
}
