/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vde-frei <vde-frei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:43:36 by vde-frei          #+#    #+#             */
/*   Updated: 2024/03/10 20:09:07 by vde-frei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

/**
 * needed for project
 */
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <bits/pthreadtypes.h>
# include <unistd.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
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
# define SEM_FORK "pSemaphoreFork"
# define SEM_WRITE "pSemaphoreWrite"
# define SEM_DEAD "pSemaphoreDead"
# define SEM_DEADW "pSemaphoreDeadWrite"
# define SEM_PHILO "pSemaphorePhilo"
# define SEM_PHILOEAT "pSemaphorePhiloEat"

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
	FORK,
	THINKING,
	DIED,
	FULL,
}	t_st;

typedef struct s_philo	t_philo;

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

/* main function */
void	check(int ac, char **av);
void	star_and_run_program(t_table *table, char **av);
bool	start_process(t_table *table);
bool	start_monitor(t_table *table);
void	wait_and_finish(t_table *table);
void	parser_input(t_table *table, char **av);
void	init(t_table *table);
void	run(int ac, char **av);
void	clean(t_table *table);
void	*monitor_count(void *table_v);

/* utils */
long	ft_atol(const char *nptr);
long	gettime(void);
char	*get_message(int type);
void	display_message(t_philo *philo, int type);
void	clean_forks(t_philo *philo);
void	take_forks(t_philo *philo);
sem_t	*ft_sem_open(char const *name, int value);
void	error_exit(const char *message);
void	*safe_malloc(size_t bytes);

/* routine function */
void	eat(t_philo *philo);
void	*monitor(void *philo_v);
void	*monitor_count(void * table_v);
void	routine(t_philo *philo_v);

/* handle string functions */
int		ft_strcpy(char *dst, const char *src);
char	*make_semaphore_name(char const *base, char *buffer, int position);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(long nb, int fd);
size_t	ft_strlen(char *str);


#endif //!PHILO_H
