/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:27:29 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/10 19:50:29 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putnbr_fd(long nb, int fd)
{
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
		ft_putchar_fd(nb + '0', fd);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

long	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (long)1000) + (tv.tv_usec / (long)1000));
}

char	*get_message(int type)
{
	if (type == EATING)
		return (" is eating\n");
	else if (type == SLEEPING)
		return (" is sleeping\n");
	else if (type == FORK)
		return (" has taken a fork\n");
	else if (type == THINKING)
		return (" is thinking\n");
	else if (type == FULL)
		return ("must eat count reached\n");
	return (" died\n");
}

void	display_message(t_philo *philo, int type)
{
	sem_wait(philo->table->write_mtx);
	sem_wait(philo->table->dead_write_mtx);
	ft_putnbr_fd(get_time() - philo->table->start, STDOUT_FILENO);
	ft_putchar_fd('\t', STDOUT_FILENO);
	if (type != FULL)
		ft_putnbr_fd(philo->position + 1, STDOUT_FILENO);
	write(STDOUT_FILENO, get_message(type), ft_strlen(get_message(type)));
	if (type < DIED)
		sem_post(philo->table->dead_write_mtx);
	sem_post(philo->table->write_mtx);
}

void	*monitor_count(void * table_v)
{
	t_table *table;
	int		total;
	int		i;

	table = (t_table*)table_v;
	total = 0;
	while (total < table->max_meals)
	{
		i = 0;
		while (i < table->ph_nb)
			sem_wait(table->philo[i++].eat_count_mtx);
		total++;
	}
	display_message(&table->philo[0], FULL);
	sem_post(table->have_died_mtx);
	return ((void*)false);
}

void	clean_forks(t_philo *philo)
{
	display_message(philo, SLEEPING);
	sem_post(philo->table->fork_mtx);
	sem_post(philo->table->fork_mtx);
	usleep(philo->table->sleep * 1000);
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
	usleep(philo->table->eat * 1000);
	philo->eat_count++;
	philo->is_eating = false;
	sem_post(philo->mutex);
	sem_post(philo->eat_count_mtx);
}

void	*monitor(void *philo_v)
{
	t_philo	*philo;

	philo = (t_philo*)philo_v;
	while (true)
	{
		sem_wait(philo->mutex);
		if (!philo->is_eating && get_time() > philo->limit)
		{
			display_message(philo, DIED);
			sem_post(philo->mutex);
			sem_post(philo->table->have_died_mtx);
			return ((void*)0);
		}
		sem_post(philo->mutex);
		usleep(1000);
	}
	return ((void*)0);
}

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

bool	start_process(t_table *table)
{
	int	i;
	
	table->start = get_time();
	i = -1;
	while (++i < table->ph_nb)
	{
		table->philo[i].pid = fork();
		if (table->philo[i].pid < 0)
			return (true);
		else if (!table->philo[i].pid)
			routine(&table->philo[i]);
		usleep(100);
	}
	return (false);
}

void	wait_and_finish(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->ph_nb)
		kill(table->philo[i++].pid, SIGKILL);
	clean(table);
}

bool	start_monitor(t_table *table)
{
	pthread_t	tid;

	if (table->max_meals > 0)
	{
		if (pthread_create(&tid, NULL, &monitor_count, (void*)table) != 0)
			return (true);
		pthread_detach(tid);
	}
	return (false);
}

void	star_and_run_program(t_table *table, char **av)
{
	parser_input(table, av);
	if (start_monitor(table) || start_process(table))
	{
		clean(table);
		error_exit("error: fatal\n");
	}
}

int	main(int ac, char **av)
{
	t_table	table;

	check(ac, av);
	star_and_run_program(&table, av);
	sem_wait(table.have_died_mtx);
	wait_and_finish(&table);
	return (EXIT_SUCCESS);
}
