/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:37:20 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/05 18:51:06 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	assign_forks(t_philo *philo, t_fork *fork, int position);
static void	philo_init(t_table *table);

/**
 * @brief Initializes the dining table.
 *
 * This function initializes the dining table by setting initial values and
 * allocating memory for philosophers and forks. It also initializes mutexes for
 * writing and table synchronization,as well as initializing
 * mutexes for each fork.
 *
 * @param table A pointer to the table structure to be initialized.
 */
void	init(t_table *table)
{
	int	i;

	i = -1;
	table->end = false;
	table->all_up = false;
	table->th_nbr = 0;
	table->philo = safe_malloc(sizeof(t_philo) * table->ph_nb);
	table->fork = safe_malloc(sizeof(t_fork) * table->ph_nb);
	table->fork->fork = sem_open(S_FORKS, O_CREAT, S_IRWXU, table->ph_nb);
	if (table->fork->fork == SEM_FAILED)
		error_exit("SEM_OPEN ERROR");

	philo_init(table);
}

/**
 * @brief Initializes the philosophers.
 *
 * This function initializes the philosophers by setting initial values,
 * assigning IDs, and initializing mutexes for each philosopher.
 *
 * @param table A pointer to the table structure containing information about
 * the dining table.
 */
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
		philo->meals = 0;
		philo->table = table;
		safe_mtx_handle(&philo->philo_mtx, INIT);
		assign_forks (philo, table->fork, i);
	}
}

/**
 * @brief Assigns forks to philosophers.
 *
 * This function assigns forks to philosophers based on their position and ID.
 *
 * @param philo A pointer to the philosopher structure to assign forks to.
 * @param fork An array of forks to be assigned.
 * @param position The position of the philosopher in the array.
 */
static void	assign_forks(t_philo *philo, t_fork *fork, int position)
{
	int	philo_nbr;

	philo_nbr = philo->table->ph_nb;
	philo->first_fork = &fork[(position + 1) % philo_nbr];
	philo->second_fork = &fork[position];
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &fork[position];
		philo->second_fork = &fork[(position + 1) % philo_nbr];
	}
}
