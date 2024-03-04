/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:27:29 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/04 19:47:31 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief The entry point of the program.
 *
 * This function serves as the entry point of the program. It parses the
 * command-line arguments, initializes the dining table, starts the dinner
 * simulation, cleans up resources, and exits with success.
 *
 * @param ac The number of command-line arguments.
 * @param av An array of strings containing the command-line arguments.
 * @return An integer indicating the exit status of the program.
 */
int	main(int ac, char **av)
{
	t_table	table;

	check(ac, av);
	parser_input(&table, av);
	init(&table);
	dinner_start(&table);
	clean(&table);
	return (EXIT_SUCCESS);
}
