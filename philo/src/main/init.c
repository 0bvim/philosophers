/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:37:20 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/27 18:45:45 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	init(t_table *table)
{
	table->end = false;
	table->philo = safe_malloc(table->ph_nb);
}
