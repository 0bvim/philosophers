/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:40:42 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/11 02:01:46 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*get_message(int type)
{
	if (type == EATING)
		return (YLW" is eating\n"RST);
	else if (type == SLEEPING)
		return (GRN" is sleeping\n"RST);
	else if (type == FORK)
		return (RED" has taken a fork\n"RST);
	else if (type == THINKING)
		return (ORG" is thinking\n"RST);
	else if (type == FULL)
		return (CYA"must eat count reached\n"RST);
	return (BLU" died\n"RST);
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
