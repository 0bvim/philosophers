/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 01:46:33 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/03 14:22:32 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <semaphore.h>

# include <stdbool.h>
# include <stddef.h>
# include <limits.h>
# include <errno.h>

# define YLW "\033[1;33m"
# define GRN "\033[1;32m"
# define RED "\033[1;31m"
# define ORG "\033[93m"
# define BLU "\033[94m"
# define CYA "\033[36m"
# define RST "\033[0m"
# define MAG "\033[95m"
# define LRED "\033[91m"

/* ANOTHER ENUMS */
enum	e_philo
{
	DEBUG_MODE,
	MAX_PHILO = 200,
};

/* PHILO STATUS */
typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

/* HANDLE TIME */
typedef enum e_time_code
{
	SECOND,
	MILLISEC,
	MICROSEC,
}	t_time_code;

typedef enum e_mtx
{
	CREATE,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	DETACH,
	JOIN
}	t_code;

typedef pthread_mutex_t	t_mtx;
typedef struct s_philo	t_philo;

typedef struct s_fork
{
	int		id;
}	t_fork;

typedef struct s_table
{
	int			ph_nb;
	int			max_meals;
	long		eat;
	long		sleep;
	long		die;
	long		start;
	bool		end;
	bool		all_up;
	sem_t		*sem_print;
	sem_t		*sem_forks;
	t_philo		*philo;
	pthread_t	monitor;
}	t_table;

struct s_philo
{
	int			id;
	bool		full;
	long		meals;
	long		last_meal;
	sem_t		philo_sem;
	t_table		*table;
};

/* entrance function */
void	check(int ac, char **av);
void	parser_input(t_table *table, char **av);
void	init_processes(t_table *table);
void	run(int ac, char **av);
void	clean(t_table *table);

/* utils */
long	ft_atol(const char *nptr);
void	error_exit(const char *message);

#endif // !PHILO_H

