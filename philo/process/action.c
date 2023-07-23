#include "../includes/philo.h"

// This function represents the eating action of a philosopher in the dining philosophers scenario.
int	eating(t_philo *philo, t_data *data)
{
	if (print_philo_action(philo, data, EATING))
		return (pthread_mutex_unlock(philo->left_fork),
			pthread_mutex_unlock(philo->right_fork), 1);
	pthread_mutex_lock(&data->time);
	philo->time_until_die = get_time();
	pthread_mutex_unlock(&data->time);
	ft_usleep(data, data->input.to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&data->meal);
	philo->meal_count++;
	pthread_mutex_unlock(&data->meal);
	return (0);
}

// This function is responsible for acquiring the necessary forks and initiating the eating process for a philosopher.
int	fork_init_eating(t_philo *philo, t_data *data)
{
	if (philo->pos == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		if (print_philo_action(philo, data, TAKEN_FORK))
			return (pthread_mutex_unlock(philo->right_fork), 1);
		pthread_mutex_lock(philo->left_fork);
		if (print_philo_action(philo, data, TAKEN_FORK))
			return (pthread_mutex_unlock(philo->right_fork),
				pthread_mutex_unlock(philo->left_fork), 1);
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		if (print_philo_action(philo, data, TAKEN_FORK))
			return (pthread_mutex_unlock(philo->left_fork), 1);
		pthread_mutex_lock(philo->right_fork);
		if (print_philo_action(philo, data, TAKEN_FORK))
			return (pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork), 1);
	}
	return (eating(philo, data));
}

// This function represents the sleeping action of a philosopher in the dining philosophers scenario.
int	sleeping(t_philo *philo, t_data *data)
{
	if (print_philo_action(philo, data, SLEEPING))
		return (1);
	ft_usleep(data, data->input.to_sleep);
	return (0);
}

// This function represents the thinking action of a philosopher in the dining philosophers scenario.
int	thinking(t_philo *philo, t_data *data)
{
	if (print_philo_action(philo, data, THINKING))
		return (1);
	return (0);
}
