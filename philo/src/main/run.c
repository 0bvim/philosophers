/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:18:44 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/26 22:53:01 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	philo_must_eat_off(int ac, char **av);
static void	philo_must_eat_on(int ac, char **av);

void	run(int ac, char **av)
{
	philo_must_eat_on(ac, av);
	philo_must_eat_off(ac, av);
}

static void	philo_must_eat_on(int ac, char **av)
{
	(void)ac;
	(void)av;
}

static void	philo_must_eat_off(int ac, char **av)
{
	(void)ac;
	(void)av;
}
