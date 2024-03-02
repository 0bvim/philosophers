/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 21:38:01 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/01 21:39:39 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

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
