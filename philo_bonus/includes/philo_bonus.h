#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <pthread.h>
# include <sys/time.h>

// actions
# define EATING			"\x1b[32m is eating\n\x1b[0m"
# define SLEEPING		"\x1b[35m is sleeping\n\x1b[0m"
# define THINKING		"\x1b[36m is thinking\n\x1b[0m"
# define TAKEN_FORK		"\x1b[33m has taken a fork\n\x1b[0m"
# define PHILO_DIED		"\x1b[31m died\n\x1b[0m"

// errors
# define TCREAT			"Error while creating/joining threads"
# define TJOIN			"Error while creating/joining threads"
# define MALLOC			"Error caused by a malloc"
# define SEM_OPEN		"Error caused by a semaphore open"
# define SEM_CLOSE		"Error caused by a semaphore close"
# define TUTO			"./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]"
# define N_PHILO		"[number_of_philosophers] must be a non null \
positive integer between 1 and 200"
# define INT			"All parameters must be a positive integer"
# define NUMBER			"All parameters must be numbers"
# define PHILO			"Error while creating t_philo structure (malloc)"
# define FORK			"Error while creating child process"

typedef struct s_philo
{
	int			pos;
	int			meal_count;
	long long	time_until_die;
	void		*memory;
	pthread_t	thread;
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
	t_input		input;
	t_philo		philo[200];
	bool		philo_dead;
	long long	time_start;
	sem_t		*time;
	sem_t		*eat;
	sem_t		*dead;
	sem_t		*fork;
	sem_t		*writing;
	pid_t		pid[200];
}				t_data;

/* -------------------------------------------------------------------------- */
/*                                   CREATE                                   */
/* -------------------------------------------------------------------------- */

// create_childs.c
int			kill_child_process(t_data *data, int until);
int			wait_all_child(t_data *data);
int			create_childs(t_data *data);

// create_data.c
int			create_data(t_data *data, int ac, char **av);
void		init_input(t_input *input, int ac, char **av);
void		init_philo(t_data *data);

// create_semaphores.c
int			init_semaphores(t_data *data);
void		destroy_semaphores(t_data *data);

/* -------------------------------------------------------------------------- */
/*                                   KERNEL                                   */
/* -------------------------------------------------------------------------- */

// parsing.c
int			is_num(char *str);
int			is_positive(int ac, char **av);
int			parsing(int ac, char **av);

// print.c
int			error_msg(char *s1, int ret_val);
int			print_philo_action(t_philo *philo, t_data *data, char *action);

/* -------------------------------------------------------------------------- */
/*                                   PROCESS                                  */
/* -------------------------------------------------------------------------- */

// actions.c
int			eating(t_data *data, t_philo *philo);
int			sleeping(t_data *data, t_philo *philo);
int			thinking(t_data *data, t_philo *philo);

// checker.c
void		*check_dead(void *arg);

// routine.c
int			check(t_data *data);
int			child(t_data *data, t_philo *philo);
int			death(t_data *data, t_philo *philo);
int			life_cycle(t_data *data, t_philo *philo);
void		single_philo(t_data *data);

// time.c
long long	get_time(void);
long long	get_time_from_start(long long time);
void		ft_usleep(t_data *data, long int time_in_ms);
void		ft_usleep_routine(t_data *data, t_philo *philo, long int time);

/* -------------------------------------------------------------------------- */
/*                                    UTILS                                   */
/* -------------------------------------------------------------------------- */

// utils.c
int			ft_strlen(char *str);
long		ft_atoi(const char *str);
void		*ft_calloc(size_t n, size_t size);

#endif
