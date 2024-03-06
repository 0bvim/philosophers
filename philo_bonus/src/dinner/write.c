/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:40:42 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/06 17:17:32 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

	(void)debug;
	elapsed = gettime(MILLISEC) - philo->table->start;
	if (philo->full)
		return ;
	safe_mtx_handle(philo->table->write_mtx, LOCK, NULL);
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
	safe_mtx_handle(philo->table->write_mtx, UNLOCK, NULL);
}
