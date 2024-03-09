/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:43:36 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/09 15:44:10 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/**
 * needed for project
 */
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

/**
 * for definitions and types
 */
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

/* semaphores definitions */
# define S_FORKS "/forks"
# define S_TABLE "/table"
# define S_PRINT "/print"
# define S_DEATH "/lock_death"

/* message errors */
# define TAKE_FORKS YLW"has taken a fork"RST
# define THINK GRN"is thinking"RST
# define SLEEP CYA"is sleeping"RST
# define EAT LRED"is eating"RST
# define DIED RED"died"RST

/* ANOTHER ENUMS */
enum	e_philo
{
	MAX_PHILO = 200,
};

/* PHILO STATUS */
typedef enum e_philo_status
{
	EATING,
	DEAD,
	FULL,
	IDLE,
	FINISH,
	SLEEPING,
}	t_st;

/* misc enum */
enum e_misc
{
	ONE = 1,
};

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

struct s_philo
{
	int		id;
	int		meals;
	t_st	state;
	long	eat;
	sem_t	*sem_philo;
	t_table	*table;
};

typedef struct s_table
{
	int			ph_nb;
	long		die;
	long		eat;
	long		sleep;
	int			max_meals;
	long		start;
	t_philo		*philo;
	sem_t		*fork_mtx;
	sem_t		*write_mtx;
	sem_t		*dead_write_mtx;
	sem_t		*have_died_mtx;
}	t_table;

struct s_philo
{
	pid_t		pid;
	int			position;
	bool		is_eating;
	long		eat_count;
	long		limit;
	long		last_meal;
	int			left_fork;
	int			right_fork;
	sem_t		*mutex;
	sem_t		*eat_count_mtx;
	t_table		*table;
};

/* entrance function */

/* str */
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
char	*ft_strdup(const char *s);
char	*ft_strmerge(char *s1, char *s2);

#endif //!PHILO_H
