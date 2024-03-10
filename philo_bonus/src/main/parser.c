/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 23:46:20 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/09 23:21:08 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strcpy(char *dst, const char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = 0;
	return (i);
}

char	*make_semaphore_name(char const *base, char *buffer, int position)
{
	int	i;

	i = ft_strcpy(buffer, base);
	while (position > 0)
	{
		buffer[i++] = (position % 10) + '0';
		position /= 10;
	}
	buffer[i] = 0;
	return (buffer);
}

sem_t	*ft_sem_open(char const *name, int value)
{
	return (sem_open(name, O_CREAT | O_EXCL, 0644, value));
}

static void	philo_init(t_table *table)
{
	int		i;
	char	semaphore[250];

	i = -1;
	while (++i < table->ph_nb)
	{
		table->philo[i].is_eating = false;
		table->philo[i].position = i;
		table->philo[i].left_fork = i;
		table->philo[i].right_fork = (i + 1) % table->ph_nb;
		table->philo[i].table = table;
		make_semaphore_name(SEM_PHILO, (char*)semaphore, i);
		sem_unlink(semaphore);
		table->philo[i].mutex = ft_sem_open(semaphore, 0);
		if (table->philo[i].mutex == SEM_FAILED)
			error_exit("Fail to open semaphore.");
		make_semaphore_name(SEM_PHILOEAT, (char*)semaphore, i);
		sem_unlink(semaphore);
		table->philo[i].eat_count_mtx = ft_sem_open(semaphore, 0);
		if (table->philo[i].eat_count_mtx == SEM_FAILED)
			error_exit("Fail to open semaphore.");
	}
}

void	init_semaphores(t_table *table)
{
	sem_unlink(SEM_FORK);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_DEADW);

	table->fork_mtx = ft_sem_open(SEM_FORK, table->ph_nb);
	if (table->fork_mtx == SEM_FAILED)
		error_exit("fail in fork semaphore creation.");
	table->write_mtx = ft_sem_open(SEM_WRITE, 1);
	if (table->write_mtx == SEM_FAILED)
		error_exit("fail in write semaphore creation.");
	table->have_died_mtx = ft_sem_open(SEM_DEAD, 0);
	if (table->have_died_mtx == SEM_FAILED)
		error_exit("fail in have died semaphore creation.");
	table->dead_write_mtx = ft_sem_open(SEM_DEADW, 1);
	if (table->dead_write_mtx == SEM_FAILED)
		error_exit("fail in dead write semaphore creation.");
}

void	parser_input(t_table *table, char **av)
{
	table->ph_nb = ft_atol(av[1]);
	if (table->ph_nb > MAX_PHILO)
		table->ph_nb = MAX_PHILO;
	table->die = (ft_atol(av[2]) * 1e3);
	table->eat = (ft_atol(av[3]) * 1e3);
	table->sleep = (ft_atol(av[4]) * 1e3);
	if (av[5])
		table->max_meals = ft_atol(av[5]);
	else
		table->max_meals = -1;
	table->fork_mtx = NULL;
	table->philo = (t_philo*)safe_malloc(sizeof(*(table->philo)) * table->ph_nb);
	philo_init(table);
	init_semaphores(table);
}
