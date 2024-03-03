/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 23:46:20 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/02 23:23:19 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo_bonus.h"

static void	init_semaphores(t_table *data);

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
void	parser_input(t_table *table, char **av) {
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

/**
 * @brief Initializes semaphores for the dining philosophers problem.
 *
 * This function initializes semaphores used for synchronization in the dining
 * philosophers problem. It creates and opens semaphores for forks and printing.
 *
 * @param data A pointer to the dining table data structure.
 */
static void	init_semaphores(t_table *data)
{
	sem_unlink("/death");
	sem_unlink("/forks");
	sem_unlink("/print");
	data->sem_forks = sem_open("/forks", O_CREAT, 0644, data->ph_nb);
	data->sem_print = sem_open("/print", O_CREAT, 0644, 1);
	if (data->sem_forks == SEM_FAILED || data->sem_print == SEM_FAILED)
	{
		clean(data);
		error_exit("SEM FAILED");
	}
	sem_unlink("/forks");
	sem_unlink("/print");
}
