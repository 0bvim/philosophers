/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:38:01 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/03 20:39:36 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_close(table->sem_print);
	sem_close(table->sem_forks);
}
