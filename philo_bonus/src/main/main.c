/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:27:29 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/11 01:17:46 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int ac, char **av)
{
	t_table	table;

	check(ac, av);
	star_and_run_program(&table, av);
	sem_wait(table.have_died_mtx);
	wait_and_finish(&table);
	return (EXIT_SUCCESS);
}
