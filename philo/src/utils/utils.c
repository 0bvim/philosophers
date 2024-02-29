/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:11:06 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/29 11:42:20 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

/*
 * @brief Function to get current time and convert.
 * param time_code Code of which kind of value wanna get.
 * return long Value converted.
 **/
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

/*
 * @brief Function to print error message and exit.
 * param message The message that should be printed.
 * return Does not return a value, just exit.
 **/
void	error_exit(const char *message)
{
	printf(RED"%s"RESET"\n", message);
	exit (EXIT_FAILURE);
}

/*
 * @brief Function to get more precise time than usleep.
 * param usec Time to adjust.
 * param table Struct with all information.
 * return Does not return a value.
 **/
void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = gettime(MICROSEC);
	while (gettime(MICROSEC) - start < usec)
	{
		if (simulation_status(table))
			break ;
		elapsed = gettime(MICROSEC) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
			while (gettime(MICROSEC) - start < usec)
				;
	}
}

