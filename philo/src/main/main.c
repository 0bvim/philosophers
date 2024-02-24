/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:27:29 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/24 01:53:26 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	no_philo_must_eat(int ac, char **av)
{
	printf("(no_philo_must_eat)%d %s\n", ac, *av);
}

void	philo_must_eat(int ac, char **av)
{
	printf("(philo_must_eat)%d %s\n", ac, *av);
}

int main(int ac, char **av)
{
	if (5 == ac)
		no_philo_must_eat(ac, av);
	else if (6 == ac)
		philo_must_eat(ac, av);
	else
	{
		printf("(Wrong arguments)%d\n", ac);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
