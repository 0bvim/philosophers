/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:27:29 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/24 01:32:05 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int main(int ac, char **av)
{
	if (5 != ac || 6 != ac)
		return (EXIT_FAILURE);
	if (5 == ac)
		no_philo_must_eat(ac, av);
	else
		philo_must_eat(ac, av);
	return (EXIT_SUCCESS);
}
