/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:38:01 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/02 03:19:52 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/**
 * @brief Cleans up resources allocated for the dining table.
 *
 * This function releases resources allocated for the dining table, including
 * destroying mutexes associated with philosophers and the table itself, and
 * freeing memory allocated for forks and philosophers.
 *
 * @param table A pointer to the table structure to be cleaned up.
 */
void	clean(t_table *table)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < table->ph_nb)
	{
		philo = table->philo + i;
		safe_mtx_handle(&philo->philo_mtx, DESTROY);
	}
	safe_mtx_handle(&table->write_mtx, DESTROY);
	safe_mtx_handle(&table->table_mtx, DESTROY);
	free(table->fork);
	free(table->philo);
}
