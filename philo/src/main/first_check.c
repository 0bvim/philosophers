/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 00:19:21 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/02 03:04:19 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_helper(void);
static bool	arg_validation(int ac, char **av);
static bool	is_digit(char c);
static bool	check_range(char **av);

/**
 * @brief Checks command-line arguments for validity.
 *
 * This function checks the command-line arguments for validity. If the number
 * of arguments is either 5 or 6 and the arguments pass validation, it returns;
 * otherwise, it prints the helper message and exits with failure.
 *
 * @param ac The number of command-line arguments.
 * @param av An array of strings containing the command-line arguments.
 */
void	check(int ac, char **av)
{
	if ((5 == ac || 6 == ac) && arg_validation(ac, av))
		return ;
	print_helper();
	exit (EXIT_FAILURE);
}

/**
 * @brief Validates command-line arguments.
 *
 * This function validates the command-line arguments. It checks if each
 * argument is a digit and if they are within the specified range.
 *
 * @param ac The number of command-line arguments.
 * @param av An array of strings containing the command-line arguments.
 * @return true if the arguments are valid, false otherwise.
 */
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

/**
 * @brief Checks if a character is a digit.
 *
 * @param c The character to be checked.
 * @return true if the character is a digit, false otherwise.
 */
static bool	is_digit(char c)
{
	return (c >= 48 && c <= 57);
}

/**
 * @brief Checks if the command-line arguments are within the specified range.
 *
 * @param av An array of strings containing the command-line arguments.
 * @return true if the arguments are within the range, false otherwise.
 */
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

/**
 * @brief Prints the helper message.
 */
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
