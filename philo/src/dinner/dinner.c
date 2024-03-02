/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:18:44 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/01 21:47:22 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	eat(t_philo *philo);

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (0 == table->max_meals)
		return ;
	else if (1 == table->ph_nb)
		safe_thread_handle(&table->philo[0].th_id, lonely_day,
			&table->philo[0], CREATE);
	else
		while (++i < table->ph_nb)
			safe_thread_handle(&table->philo[i].th_id, dinner_simulation,
				&table->philo[i], CREATE);
	safe_thread_handle(&table->monitor, monitor, table, CREATE);
	table->start = gettime(MILLISEC);
	set_bool(&table->table_mtx, &table->all_up, true);
	i = -1;
	while (++i < table->ph_nb)
		safe_thread_handle(&table->philo[i].th_id, NULL, NULL, JOIN);
	set_bool(&table->table_mtx, &table->end, true);
	safe_thread_handle(&table->monitor, NULL, NULL, JOIN);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISEC));
	increase_long(&philo->table->table_mtx, &philo->table->th_nbr);
	unsync_philos(philo);
	while (!simulation_status(philo->table))
	{
		if (get_bool(&philo->philo_mtx, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo, DEBUG_MODE);
		precise_usleep(philo->table->sleep, philo->table);
		thinking(philo, false);
	}
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mtx_handle(&philo->first_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	safe_mtx_handle(&philo->second_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo, DEBUG_MODE);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISEC));
	philo->meals++;
	write_status(EATING, philo, DEBUG_MODE);
	precise_usleep(philo->table->eat, philo->table);
	if (philo->table->max_meals > 0 && philo->meals == philo->table->max_meals)
		set_bool(&philo->philo_mtx, &philo->full, true);
	safe_mtx_handle(&philo->first_fork->fork, UNLOCK);
	safe_mtx_handle(&philo->second_fork->fork, UNLOCK);
}

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo, DEBUG_MODE);
	if (philo->table->ph_nb % 2 == 0)
		return ;
	t_eat = philo->table->eat;
	t_sleep = philo->table->sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->table);
}

void	*lonely_day(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->table);
	set_long(&philo->philo_mtx, &philo->last_meal, gettime(MILLISEC));
	increase_long(&philo->table->table_mtx, &philo->table->th_nbr);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_status(philo->table))
		precise_usleep(200, philo->table);
	return (NULL);
}
