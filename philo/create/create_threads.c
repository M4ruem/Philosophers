#include "../includes/philo.h"

// This function creates and starts the required threads.
int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	data->time_start = get_time();
	if (pthread_create(&data->checker, NULL, check_dead, (void *)data))
		return (error_msg(THREADS, 1));
	while (i < data->input.number_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &routine,
				(void *)&data->philo[i]))
			return (error_msg(THREADS, 2));
		i += 2;
		if (i >= data->input.number_philo && i % 2 == 0)
		{
			i = 1;
			if (data->input.to_eat < data->input.to_die)
				ft_usleep(data, data->input.to_eat);
			else
				ft_usleep(data, data->input.to_die / 2);
		}
		usleep(30);
	}
	return (join_threads(data));
}

// This function joins the threads that were created.
int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_join(data->checker, NULL))
		return (error_msg(THREADS, 3));
	while (i < data->input.number_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			return (error_msg(THREADS, 4));
		i++;
	}
	return (0);
}
