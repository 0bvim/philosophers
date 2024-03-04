/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:11:06 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/03 22:44:53 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * @brief Retrieves the current time.
 *
 * This function retrieves the current time in different units based on the
 * specified time code.
 *
 * @param time_code The time code indicating the desired time unit.
 * @return The current time in the specified unit.
 */
long	gettime(t_time_code time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit ("Gettimeofday failed.");
	if (SECOND == time_code)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (MILLISEC == time_code)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (MICROSEC == time_code)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Wrong input to gettime");
	return (42);
}

/**
 * @brief Exits the program with an error message.
 *
 * This function prints an error message in red color and exits the program
 * with failure status.
 *
 * @param message The error message to be displayed.
 */
void	error_exit(const char *message)
{
	printf(RED"%s"RST"\n", message);
	exit (EXIT_FAILURE);
}

void	ft_usleep(long	sleep_time)
{
	long	start;
	
	start = gettime(MILLISEC);
	while ((gettime(MILLISEC) - start) < sleep_time)
		usleep(500);
}

void	sleep_even(t_table *table)
{
	if (table->philo.id % 2 == 0)
		ft_usleep(table->eat - 10);
}
