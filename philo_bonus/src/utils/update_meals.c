/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_meals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 21:43:15 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/03 22:33:57 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_last_eat_time(t_table *table)
{
	long	time;

	sem_wait(table->philo.philo_sem);
	time = table->philo.last_meal;
	sem_post(table->philo.philo_sem);
	return (time);
}

void	last_meal_update(t_table *table)
{
	sem_wait(table->philo.philo_sem);
	table->philo.last_meal = gettime(MILLISEC);
	sem_post(table->philo.philo_sem);
}

t_philo_status	get_philo_state(t_table *table)
{
	t_philo_status	state;

	sem_wait(table->philo.philo_sem);
	state = table->philo.state;
	sem_post(table->philo.philo_sem);
	return (state);
}

void	set_philo_state(t_table *table, t_philo_status state)
{
	sem_wait(table->philo.philo_sem);
	table->philo.state = state;
	sem_post(table->philo.philo_sem);
}

bool	philo_died(t_table *table)
{
	if (get_philo_state(table) != EATING
		&& gettime(MILLISEC) - get_last_eat_time(table) > table->die)
		return (true);
	return (false);
}
