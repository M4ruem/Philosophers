/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:45:04 by cormiere          #+#    #+#             */
/*   Updated: 2023/07/23 11:51:50 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// This function checks if a philosopher has died.
int	is_philo_dead(t_philo *philo, t_data *data)
{
	long long	time;

	sem_wait(data->time);
	time = get_time_from_start(philo->time_until_die);
	sem_post(data->time);
	if (time > data->input.to_die)
	{
		sem_wait(data->dead);
		data->philo_dead = true;
		sem_post(data->dead);
		sem_wait(data->writing);
		printf("%lld	%d %s", get_time_from_start(data->time_start),
			philo->pos + 1, PHILO_DIED);
		return (1);
	}
	ft_usleep_routine(data, philo, 1);
	return (0);
}

// This function checks if a philosopher has eaten the required number of meals.
int	has_eaten(t_data *data, t_philo *philo)
{
	sem_wait(data->eat);
	if (philo->meal_count >= data->input.number_meal)
	{
		sem_post(data->eat);
		return (1);
	}
	sem_post(data->eat);
	return (0);
}

// This function is a thread routine that continuously checks if
// a philosopher has died or if the stopping condition is met.
void	*check_dead(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->memory;
	while (!death(data, philo)
		&& (!data->input.number_meal || !has_eaten(data, philo)))
	{
		if (is_philo_dead(philo, data))
		{
			pthread_detach(philo->thread);
			return (NULL);
		}
	}
	pthread_detach(philo->thread);
	return (NULL);
}
