#include "../includes/philo.h"

// This function returns the current time in milliseconds.
long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

// This function calculates the time elapsed since the program started.
long long	get_time_from_start(long long time_to_wait)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (time_to_wait > 0)
		return ((time.tv_sec * 1000) + (time.tv_usec / 1000) - time_to_wait);
	return (0);
}

// This function introduces a delay in milliseconds, while checking for the termination condition.
void	ft_usleep(t_data *data, long int time_in_ms)
{
	long int	start_time;

	start_time = get_time_from_start(data->time_start);
	while (get_time_from_start(data->time_start) < start_time + time_in_ms)
	{
		pthread_mutex_lock(&data->stop);
		if (data->philo_dead)
		{
			pthread_mutex_unlock(&data->stop);
			return ;
		}
		pthread_mutex_unlock(&data->stop);
		usleep(time_in_ms / 20);
	}
}
