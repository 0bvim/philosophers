/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 21:18:44 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/11 01:17:17 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	routine(t_philo *philo_v)
{
	t_philo	*philo;
	pthread_t	tid;

	philo = (t_philo*)philo_v;
	philo->last_meal = get_time();
	philo->limit = philo->last_meal + philo->table->die;
	if (pthread_create(&tid, NULL, &monitor, philo) != 0)
		exit(EXIT_FAILURE);
	pthread_detach(tid);
	while (true)
	{
		take_forks(philo);
		eat(philo);
		clean_forks(philo);
		display_message(philo, THINKING);
	}
	exit (EXIT_SUCCESS);
}

void	clean_forks(t_philo *philo)
{
	display_message(philo, SLEEPING);
	sem_post(philo->table->fork_mtx);
	sem_post(philo->table->fork_mtx);
	usleep(philo->table->sleep * 1e3);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->table->fork_mtx);
	display_message(philo, FORK);
	sem_wait(philo->table->fork_mtx);
	display_message(philo, FORK);
}

void	eat(t_philo *philo)
{

	sem_wait(philo->mutex);
	philo->is_eating = true;
	philo->last_meal = get_time();
	philo->limit = philo->last_meal + philo->table->die;
	display_message(philo, EATING);
	usleep(philo->table->eat * 1e3);
	philo->eat_count++;
	philo->is_eating = false;
	sem_post(philo->mutex);
	sem_post(philo->eat_count_mtx);
}
