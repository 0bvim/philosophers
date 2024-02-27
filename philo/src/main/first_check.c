/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 00:19:21 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/26 22:52:44 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	print_helper(void);
static bool	arg_validation(int ac, char **av);
static bool	is_digit(char c);

void	check(int ac, char **av)
{
	if ((5 == ac || 6 == ac) && arg_validation(ac, av))
		return ;
	print_helper();
	exit (EXIT_FAILURE);
}

static void	print_helper(void)
{
	printf(MAGENTA"Instructions to execute:"RESET"\n");
	printf("1st arg: "YELLOW"Number of Philoshophers"RESET"\n");
	printf("2nd arg: "CYAN"time to "RESET RED"die"RESET"\n");
	printf("3nd arg: "CYAN"time to "RESET ORANGE"eat"RESET"\n");
	printf("4th arg: "CYAN"time to "RESET BLUE"sleep"RESET"\n");
	printf("5th arg: "CYAN"number of times each must eat. (opt)"RESET"\n");
	printf("Example 4 args: "LRED"./philo 5 800 200 200"RESET"\n");
	printf("Example 5 args: "LRED"./philo 5 800 200 200 7"RESET"\n");
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
	return (true);
}

static bool	is_digit(char c)
{
	return (c >= 48 && c <= 57);
}
