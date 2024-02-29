/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:40:42 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/29 12:37:52 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	write_status_debug(t_philo_status status, t_philo *philo, long el)
{
	if (TAKE_FIRST_FORK == status && !simulation_status(philo->table))
		printf(MAG"%6ld"RST" %d has taken the 1° fork 🍽"
			"\t\t\tn°"BLU"[🍴 %d 🍴]\n"RST, el, philo->id,
			philo->first_fork->id);
	else if (TAKE_SECOND_FORK == status && !simulation_status(philo->table))
		printf(MAG"%6ld"RST" %d has taken the 2° fork 🍽"
			"\t\t\tn°"BLU"[🍴 %d 🍴]\n"RST, el, philo->id,
			philo->second_fork->id);
	else if (EATING == status && !simulation_status(philo->table))
		printf(YLW"%6ld"LRED" %d is eating 🍝"
			"\t\t\t"YLW"[🍝 %ld 🍝]\n"RST, el, philo->id, philo->meals);
	else if (SLEEPING == status && !simulation_status(philo->table))
		printf(MAG"%6ld"RST" %d is sleeping 😴\n", el, philo->id);
	else if (THINKING == status && !simulation_status(philo->table))
		printf(MAG"%6ld"RST" %d is thinking 🤔\n", el, philo->id);
	else if (DIED == status)
		printf(RED"\t\t💀💀💀 %6ld %d died   💀💀💀\n"RST, el, philo->id);
}

void	write_status(t_philo_status status, t_philo *philo, bool debug)
{
	long	elapsed;

	elapsed = gettime(MILLISEC) - philo->table->start;
	if (philo->full)
		return ;
	safe_mtx_handle(&philo->table->write_mtx, LOCK);
	if (debug)
		write_status_debug(status, philo, elapsed);
	else
	{
		if ((TAKE_FIRST_FORK == status || TAKE_SECOND_FORK == status)
			&& !simulation_status(philo->table))
			printf(RED"%-6ld"RST"%d has taken a fork\n", elapsed, philo->id);
		else if (EATING == status && !simulation_status(philo->table))
			printf(YLW"%-6ld"RST"%d is eating\n", elapsed, philo->id);
		else if (SLEEPING == status && !simulation_status(philo->table))
			printf(CYA"%-6ld"RST"%d is sleeping\n", elapsed, philo->id);
		else if (THINKING == status && !simulation_status(philo->table))
			printf(GRN"%-6ld"RST"%d is thinking\n", elapsed, philo->id);
		else if (DIED == status && !simulation_status(philo->table))
			printf(LRED"%-6ld %d died\n"RST, elapsed, philo->id);
	}
	safe_mtx_handle(&philo->table->write_mtx, UNLOCK);
}
