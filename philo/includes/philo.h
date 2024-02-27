/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:43:36 by vde-frei          #+#    #+#             */
/*   Updated: 2024/02/27 19:11:15 by vde-frei         ###   ########.fr       */
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

enum	e_philo
{
	MAX_PHILO = 200
};

typedef enum	e_mtx
{
	CREATE,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	DETACH
}	t_code;

typedef pthread_mutex_t	t_mtx;
typedef struct s_philo	t_philo;

typedef struct s_fork
{
	int		id;
	t_mtx	fork;
}	t_fork;

typedef struct s_table
{
	int		ph_nb;
	int		max_meals;
	long	eat;
	long	sleep;
	long	die;
	long	start;
	bool	end;
	t_fork	*fork;
	t_philo	*philo;
}	t_table;

struct s_philo
{
	int			id;
	bool		full;
	long		meals;
	long		last_meal;
	t_fork		*left;
	t_fork		*right;
	pthread_t	th_id;
	t_table		table;
};

/* entrance function */
void	check(int ac, char **av);
void	init(t_table *table);
void	run(int ac, char **av);

/* utils */
long	ft_atol(const char *nptr);

/* wrapper functions */
void	*safe_malloc(size_t bytes)

#endif // !PHILO_H
