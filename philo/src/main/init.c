/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:37:20 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/29 11:43:06 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	philo_init(t_table *table);
static void	assign_forks(t_philo *philo, t_fork *fork, int position);

/**
 * @brief function alloc structs.
 * @param table Struct with all the things.
 * @return Doest not have a return value.
 **/
void	init(t_table *table)
{
	int	i;

	i = -1;
	table->end = false;
	table->philo = safe_malloc(sizeof(t_philo) * table->ph_nb);
	table->fork = safe_malloc(sizeof(t_fork) * table->ph_nb);
	safe_mtx_handle(&table->table_mtx, INIT);
	safe_mtx_handle(&table->write_mtx, INIT);
	while (++i < table->ph_nb)
	{
		safe_mtx_handle(&table->fork[i].fork, INIT);
		table->fork[i].id = i;
	}
	philo_init(table);
}

/**
 * @brief function alloc philo struct.
 * @param table Struct with all the things.
 * @return Doest not have a return value.
 **/
static void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->ph_nb)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->last_meal = 0;
		philo->table = table;
		assign_forks (philo, table->fork, i);
	}
}

/**
 * @brief function to assigne forks to each philo
 * @param philo Struct with all philo information.
 * @param fork Struct with fork content.
 * @return Doest not have a return value.
 **/
static void	assign_forks(t_philo *philo, t_fork *fork, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->ph_nb;
	philo->first_fork = &fork[position];
	philo->second_fork = &fork[(position + 1) % philo_nbr];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &fork[position];
		philo->second_fork = &fork[(position + 1) % philo_nbr];
	}
}
