/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:27:29 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/09 21:35:26 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>


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
	return ((tv.tv_sec * (long)1e3) + (tv.tv_usec / 1e3));
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

void	routine(t_philo *philo)
{
	//TODO: Philo function
	//remember to insert exit at the end;
	(void)philo;
}

bool	start_process(t_table *table)
{
	int	i;
	
	i = -1;
	table->start = get_time();
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
		if (pthread_create(&tid, NULL, &monitor_count, (void*)table)!= 0)
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
	wait_and_finish(&table);
	return (EXIT_SUCCESS);
}
