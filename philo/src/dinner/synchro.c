/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:16:01 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/29 10:35:10 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/*
 * @brief Wait all threads to syncronize.
 * @param mtx Mutex variable to verified.
 * @param value Value to get.
 * @return Does not return.
 **/
void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_up))
		;
}
