/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:37:20 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/06 21:27:43 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	table->end = false;
	table->all_up = false;
	table->th_nbr = 0;
	table->philo = safe_malloc(sizeof(t_philo) * table->ph_nb);
	table->fork = sem_open(S_FORKS, O_CREAT, S_IRWXU, table->ph_nb);
	if (table->fork == SEM_FAILED)
		sem_exit("Failed to open the semaphore", table);
	table->write_mtx = sem_open(S_PRINT, O_CREAT, S_IRWXU, ONE);
	if (table->write_mtx == SEM_FAILED)
		sem_exit("Failed to open the semaphore", table);
	table->table_mtx = sem_open(S_TABLE, O_CREAT, S_IRWXU, ONE);
	if (table->table_mtx == SEM_FAILED)
		sem_exit("Failed to open the semaphore", table);
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
		// assign_forks (philo, table->fork, i);
	}
}
