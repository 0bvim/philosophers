/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:18:44 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/27 14:38:56 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	philo_must_eat(int ac, char **av, bool must);
void	init_table(int ac, char **av);

void	run(int ac, char **av)
{
	if (5 == ac)
		philo_must_eat(ac, av, false);
	else
		philo_must_eat(ac, av, true);
}

void	init_table(int ac, char **av)
{
	t_table	*table;
	// t_philo	*philo[table->pos];

	(void)ac;
	table = malloc(sizeof(t_table));
	if (!table)
		exit(EXIT_FAILURE);
	table->pos = ft_atoi(av[1]);
	if (table->pos > MAX_PHILO)
		table->pos = MAX_PHILO;
	printf("philo nbr %d\n", table->pos);
	// philos[s]
	// table->philo[table->pos] = (t_philo*)malloc(sizeof(t_philo) * table->pos);
	// if (!table->philo)
	// 	exit(EXIT_FAILURE);
	//
}

static void	philo_must_eat(int ac, char **av, bool must)
{
	(void)must;
	init_table(ac, av);
}

