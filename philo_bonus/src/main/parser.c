/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 23:46:20 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/09 15:47:00 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_init(t_table *table)
{
	int		i;
	char	semaphores[250];

	i = -1;
	while (++i < table->ph_nb)
	{
		table->philo[i].is_eating = false;
		table->philo[i].position = i;
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->ph_nb;
		table->philo[i].table = table;
		//TODO: make function to build semaphores name
	}
}

void	parser_input(t_table *table, char **av)
{
	table->ph_nb = ft_atol(av[1]);
	if (table->ph_nb > MAX_PHILO)
		table->ph_nb = MAX_PHILO;
	table->die = (ft_atol(av[2]) * 1e3);
	table->eat = (ft_atol(av[3]) * 1e3);
	table->sleep = (ft_atol(av[4]) * 1e3);
	if (av[5])
		table->max_meals = ft_atol(av[5]);
	else
		table->max_meals = -1;
	table->fork_mtx = NULL;
	table->philo = (t_philo*)safe_malloc(sizeof(*(table->philo)) * table->ph_nb);
	//TODO: init philos
	//TODO: init semaphores
		

}
