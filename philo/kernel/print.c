#include "../includes/philo.h"

// This function displays an error message and returns a specified return value.
int	error_msg(char *s1, int ret_val)
{
	if (s1)
	{
		write(STDERR_FILENO, s1, ft_strlen(s1));
		write(STDERR_FILENO, "\n", 1);
	}
	return (ret_val);
}

// This function prints an action performed by a philosopher.
int	print_philo_action(t_philo *philo, t_data *data, char *action)
{
	pthread_mutex_lock(&data->writing);
	pthread_mutex_lock(&data->stop);
	if (data->philo_dead == true)
	{
		pthread_mutex_unlock(&data->stop);
		pthread_mutex_unlock(&data->writing);
		return (1);
	}
	pthread_mutex_unlock(&data->stop);
	printf("%lld	%d%s", get_time_from_start(data->time_start),
		philo->pos + 1, action);
	pthread_mutex_unlock(&data->writing);
	return (0);
}
