/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:35:35 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/04 11:59:26 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eat(t_table *table)
{
	if (take_forks(table))
		return (1);
	last_meal_update(table);
	set_philo_state(table, EATING);
	if (print_msg(table, "is eating"))
	{
		drop_forks(table);
		return (1);
	}
	ft_usleep(table->sleep);
	drop_forks(table);
	table->philo.meals++;
	if (philo_full(table))
		return (1);
	return (0);
	
}

int	take_forks(t_table *table)
{
	sem_wait(table->sem_forks);
	if (print_msg(table, "has taken a fork" ))
		sem_post(table->sem_forks);
	if (table->ph_nb == 1)
		return (1);
	sem_wait(table->sem_forks);
	if (should_stop(get_philo_state(table)))
	{
		drop_forks(table);
		return (1);
	}
	if (print_msg(table, "has taken a fork" ))
	{
		drop_forks(table);
		return (1);
	}
	return (0);
}

int	drop_forks(t_table *table)
{
	sem_post(table->sem_forks);
	sem_post(table->sem_forks);
	return (0);
}

bool	philo_full(t_table *table)
{
	if (!table->max_meals)
		return (false);
	if (table->max_meals <= table->philo.meals)
	{
		set_philo_state(table, FULL);
		return (true);
	}
	return (false);
}
