/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:40:42 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/11 01:16:06 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
