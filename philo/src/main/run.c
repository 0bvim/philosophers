/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:18:44 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/27 17:55:23 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// static void	philo_must_eat(int ac, char **av, bool must);
// t_table	*init_table(int ac, char **av);

// void	run(int ac, char **av)
// {
// 	if (5 == ac)
// 		philo_must_eat(ac, av, false);
// 	else
// 		philo_must_eat(ac, av, true);
// }

// t_table	*init_table(int ac, char **av)
// {
// 	t_table	*table;
//
// 	(void)ac;
// 	table = malloc(sizeof(t_table));
// 	if (!table)
// 		exit(EXIT_FAILURE);
// 	table->pos = ft_atoi(av[1]);
// 	if (table->pos > MAX_PHILO)
// 		table->pos = MAX_PHILO;
// 	table->philo[table->pos] = malloc(sizeof(t_philo) * table->pos);
// 	philo_allocation(table->philo, table->pos);
// 	return (table);
// }
//
// static void	philo_must_eat(int ac, char **av, bool must)
// {
// 	(void)must;
// 	t_table	*table;
//
// 	table = init_table(ac, av);
//
// }
//
// static void	philo_allocation(t_philo **philo, int pos)
// {
// 	int 	i;
//
// 	i = 0;
// 	while (i < pos)
// 		philo[i++] = malloc(sizeof(t_philo));
// }
