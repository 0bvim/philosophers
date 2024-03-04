/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:40:42 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/02 02:59:24 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Writes the status of a philosopher in debug mode.
 *
 * This function writes the status of a philosopher in debug mode. It prints
 * detailed messages including the elapsed time since the start of the
 * simulation and specific information about the philosopher's actions.
 *
 * @param status The status of the philosopher.
 * @param philo A pointer to the philosopher structure.
 * @param el The elapsed time since the start of the simulation.
 */
static void	write_status_debug(t_st status, t_philo *philo, long el)
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

/**
 * @brief Writes the status of a philosopher.
 *
 * This function writes the status of a philosopher. It calculates the elapsed
 * time since the start of the simulation, then prints the appropriate status
 * message based on the current status of the philosopher. If the philosopher is
 * already full, it returns without printing anything.
 *
 * @param status The status of the philosopher.
 * @param philo A pointer to the philosopher structure.
 * @param debug A boolean indicating whether to print debug messages.
 */
void	write_status(t_st status, t_philo *philo, bool debug)
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
			printf(RED"%-6ld""%d has taken a fork\n"RST, elapsed, philo->id);
		else if (EATING == status && !simulation_status(philo->table))
			printf(YLW"%-6ld""%d is eating\n"RST, elapsed, philo->id);
		else if (SLEEPING == status && !simulation_status(philo->table))
			printf(CYA"%-6ld""%d is sleeping\n"RST, elapsed, philo->id);
		else if (THINKING == status && !simulation_status(philo->table))
			printf(GRN"%-6ld""%d is thinking\n"RST, elapsed, philo->id);
		else if (DIED == status && !simulation_status(philo->table))
			printf(LRED"%-6ld %d died\n"RST, elapsed, philo->id);
	}
	safe_mtx_handle(&philo->table->write_mtx, UNLOCK);
}
