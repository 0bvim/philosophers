/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 23:46:20 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/29 23:50:43 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	parser_input(t_table *table, char **av)
{
	table->ph_nb = ft_atol(av[1]);
	table->die = ft_atol(av[2]);
	table->eat = ft_atol(av[3]);
	table->sleep = ft_atol(av[4]);
	if (av[5])
		table->max_meals = ft_atol(av[5]);
	else
	 table->max_meals = -1;
}
