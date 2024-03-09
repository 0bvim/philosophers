/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:27:29 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/09 15:34:19 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


void	star_and_run_program(t_table *table, char **av)
{
	init(table);
	parser_input(table, av);

}

int	main(int ac, char **av)
{
	t_table	table;

	check(ac, av);
	star_and_run_program(&table, av);
	dinner_start(&table);
	clean(&table);
	return (EXIT_SUCCESS);
}
