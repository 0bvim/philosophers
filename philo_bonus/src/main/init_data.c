/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:24:51 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/04 15:34:37 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_semaphore(t_table *table)
{
	sem_unlink("/death");
	sem_unlink("/forks");
	sem_unlink("/print");
	table->sem_forks = sem_open("/forks", O_CREAT, 0644, table->ph_nb);
	table->sem_print = sem_open("/print", O_CREAT, 0644, 1);
	if (table->sem_forks == SEM_FAILED || table->sem_print == SEM_FAILED)
		error_exit("SEM FAILED");
	// sem_unlink("/forks");
	// sem_unlink("/print");
}

void	init_data(t_table *table, char **av)
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
	table->philo.state = IDLE;
	table->philo.table = table;
	table->philo.meals = 0;
	init_semaphore(table);
}
