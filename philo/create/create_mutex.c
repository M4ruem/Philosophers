#include "../includes/philo.h"

// This function initializes the mutexes used for synchronization.
int	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->writing, NULL))
		return (error_msg(MUTEX_INIT, 1));
	if (pthread_mutex_init(&data->stop, NULL))
		return (pthread_mutex_destroy(&data->writing), error_msg(MUTEX_INIT, 2));
	if (pthread_mutex_init(&data->time, NULL))
		return (pthread_mutex_destroy(&data->writing),
			pthread_mutex_destroy(&data->stop), error_msg(MUTEX_INIT, 3));
	if (pthread_mutex_init(&data->meal, NULL))
		return (pthread_mutex_destroy(&data->writing),
			pthread_mutex_destroy(&data->stop),
			pthread_mutex_destroy(&data->time), error_msg(MUTEX_INIT, 4));
	return (init_fork_mutex(data));
}

// This function initializes the mutexes used for the forks.
int	init_fork_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input.number_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (destroy_mutexes(data, i), error_msg(MUTEX_INIT, 5));
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->input.number_philo)
	{
		data->philo[i].left_fork = &data->fork[i];
		if (i == data->input.number_philo - 1)
			data->philo[i].right_fork = &data->fork[0];
		else
			data->philo[i].right_fork = &data->fork[i + 1];
		i++;
	}
	return (0);
}

// This function destroys mutexes up to a specified index.
void	destroy_mutexes(t_data *data, int n)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->meal);
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->stop);
	while (i < n)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
}
