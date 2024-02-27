/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:43:36 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/26 22:51:47 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/**
 * needed for project
 */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

/**
 * for definitions and types
 */
# include <stdbool.h>
# include <stddef.h>
# include <limits.h>
# include <inttypes.h>

# define YELLOW "\033[1;33m"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"
# define ORANGE "\033[93m"
# define BLUE "\033[94m"
# define CYAN "\033[36m"
# define RESET "\033[0m"
# define MAGENTA "\033[95m"
# define LRED "\033[91m"

typedef struct s_time
{
	double	eat;
	double	sleep;
	double	die;
}	t_time;

typedef struct s_fork
{
	int	right;
	int	left;
}	t_fork;

typedef struct s_philo
{
	t_time	*time;
	t_fork	*fork;
}	t_philo;

typedef struct s_table
{
	int		ph_qty;
	t_philo	*philo;
	t_time	*time;

}	t_table;

/* entrance function */
void	check(int ac, char **av);
void	run(int ac, char **av);

#endif // !PHILO_H
