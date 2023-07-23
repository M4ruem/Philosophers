#include "../includes/philo.h"

// This function checks if a philosopher has eaten the required number of meals.
int	has_eaten(t_data *data, int i)
{
	pthread_mutex_lock(&data->meal);
	if (data->philo[i].meal_count < data->input.number_meal)
	{
		pthread_mutex_unlock(&data->meal);
		return (0);
	}
	pthread_mutex_unlock(&data->meal);
	return (1);
}

// This function is executed by a separate thread to continuously check if a philosopher has died or fulfilled the required number of meals.
void	*check_dead(void *arg)
{
	int		i;
	t_data	*data;

	i = 0;
	data = (t_data *)arg;
	if (data->input.number_meal)
	{
		while (!data->philo_dead && !has_eaten(data, i))
			if (is_philo_dead(data, &i))
				return (NULL);
	}
	else
	{
		while (!data->philo_dead)
			if (is_philo_dead(data, &i))
				return (NULL);
	}
	return (NULL);
}

// This function checks if a philosopher is dead based on the time elapsed since their last meal.
int	is_philo_dead(t_data *data, int *i)
{
	long long	time;

	if (*i == data->input.number_philo - 1)
		*i = 0;
	pthread_mutex_lock(&data->time);
	time = get_time_from_start(data->philo[(*i)].time_until_die);
	pthread_mutex_unlock(&data->time);
	if (time > data->input.to_die)
	{
		pthread_mutex_lock(&data->stop);
		data->philo_dead = true;
		pthread_mutex_unlock(&data->stop);
		pthread_mutex_lock(&data->writing);
		printf("%lld	%d %s", get_time_from_start(data->time_start),
			*i + 1, PHILO_DIED);
		pthread_mutex_unlock(&data->writing);
		return (1);
	}
	ft_usleep(data, 1);
	(*i)++;
	return (0);
}
