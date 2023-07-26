/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:56 by cormiere          #+#    #+#             */
/*   Updated: 2023/07/24 15:05:45 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

// actions
# define EATING			"\x1b[32m is eating\n\x1b[0m"
# define SLEEPING		"\x1b[35m is sleeping\n\x1b[0m"
# define THINKING		"\x1b[36m is thinking\n\x1b[0m"
# define TAKEN_FORK		"\x1b[33m has taken a fork\n\x1b[0m"
# define PHILO_DIED		"\x1b[31m died\n\x1b[0m"

// errors
# define MALLOC			"Error caused by a malloc"
# define MUTEX_INIT		"Error caused by a mutex init"
# define MUTEX_DES		"Error caused by a mutex destruction"
# define TUTO			"./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define N_PHILO		"[number_of_philosophers] must be a non null \
positive integer between 1 and 200"
# define INT			"All parameters must be a positive integer"
# define NUMBER			"All parameters must be numbers"
# define THREADS		"Error while creating/joining threads"
# define PHILO			"Error while creating t_philo structure (malloc)"
# define FORK			"Error while creating fork mutex"

typedef struct s_philo
{
	int				pos;
	int				meal_count;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	long long		time_until_die;
	void			*memory;
}				t_philo;

typedef struct s_input
{
	long	to_die;
	long	to_eat;
	long	to_sleep;
	int		number_meal;
	int		number_philo;
}				t_input;

typedef struct s_data
{
	pthread_t		checker;
	bool			philo_dead;
	long long		time_start;
	pthread_mutex_t	stop;
	pthread_mutex_t	meal;
	pthread_mutex_t	time;
	pthread_mutex_t	writing;
	pthread_mutex_t	fork[200];
	t_input			input;
	t_philo			philo[200];
}				t_data;

/* -------------------------------------------------------------------------- */
/*                                   CREATE                                  */
/* -------------------------------------------------------------------------- */

// create_data.c
int			create_data(t_data *data, int ac, char **av);
void		init_input(t_input *input, int ac, char **av);
void		init_philo(t_data *data);

// create_threads.c
int			init_mutex(t_data *data);
int			init_fork_mutex(t_data *data);
void		destroy_mutexes(t_data *data, int n);

// create_threads.c
int			create_threads(t_data *data);
int			join_threads(t_data *data);

/* -------------------------------------------------------------------------- */
/*                                   KERNEL                                   */
/* -------------------------------------------------------------------------- */

// parsing.c
int			is_num(char *str);
int			is_positive_int(int ac, char **av);
int			parsing(int ac, char **av);

// print.c
int			error_msg(char *s1, int ret_val);
int			print_philo_action(t_philo *philo, t_data *data, char *action);

/* -------------------------------------------------------------------------- */
/*                                   PROCESS                                  */
/* -------------------------------------------------------------------------- */

// actions.c
int			eating(t_philo *philo, t_data *data);
int			fork_init_eating(t_philo *philo, t_data *data);
int			sleeping(t_philo *philo, t_data *data);
int			thinking(t_philo *philo, t_data *data);

// checker.c
int			has_eaten(t_data *data, int i);
void		*check_dead(void *arg);
int			is_philo_dead(t_data *data, int *i);

// routine.c
void		*routine(void *arg);
int			life_cycle(t_philo *philo, t_data *data);
void		single_philo(t_data *data);

// time.c
long long	get_time(void);
long long	get_time_from_start(long long time);
void		ft_usleep(t_data *data, long int time_in_ms);

/* -------------------------------------------------------------------------- */
/*                                    UTILS                                   */
/* -------------------------------------------------------------------------- */

// utils.c
int			ft_strlen(char *str);
long		ft_atoi(const char *str);
void		*ft_calloc(size_t n, size_t size);

#endif
