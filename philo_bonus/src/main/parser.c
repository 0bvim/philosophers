/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 23:46:20 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/04 19:47:31 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Parses input arguments and initializes part of the dining table.
 *
 * This function parses the input arguments provided from the command line and
 * initializes the dining table structure accordingly. It sets the number of
 * philosophers, time to die, time to eat, time to sleep,
 * and maximum number of meals.
 *
 * @param table A pointer to the table structure to be initialized.
 * @param av An array of strings containing the command-line arguments.
 */
void	parser_input(t_table *table, char **av)
{
	table->ph_nb = ft_atol(av[1]);
	if (table->ph_nb > MAX_PHILO)
		table->ph_nb = MAX_PHILO;
	table->die = (ft_atol(av[2]) * 1e3);
	table->eat = (ft_atol(av[3]) * 1e3);
	table->sleep = (ft_atol(av[4]) * 1e3);
	if (av[5])
		table->max_meals = ft_atol(av[5]);
	else
		table->max_meals = -1;
}
