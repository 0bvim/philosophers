/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:38:01 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/06 17:42:17 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>

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

	safe_mtx_handle(table->write_mtx, DESTROY, NULL);
	safe_mtx_handle(table->table_mtx, DESTROY, NULL);
	free(table->fork);
	free(table->philo);
}

void	sem_exit(char *msg, sem_t *to_close, sem_t *to_close2)
{
	if (to_close)
		sem_close(to_close);
	if (to_close2)
		sem_close(to_close2);
	error_exit(msg);
}
