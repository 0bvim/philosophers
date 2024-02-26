/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 00:19:21 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/26 01:16:54 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	philo_must_eat(int ac, char **av);
void	no_philo_must_eat(int ac, char **av);

void	check_and_run(int ac, char **av)
{
	if (5 == ac)
		no_philo_must_eat(ac, av);
	else if (6 == ac)
		philo_must_eat(ac, av);
	else
	{
		print_helper();
		exit (EXIT_FAILURE);
	}
}

void	print_helper(void)
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

void	no_philo_must_eat(int ac, char **av)
{
	(void)ac;
	(void)av;
}

void	philo_must_eat(int ac, char **av)
{
	(void)ac;
	(void)av;
}
