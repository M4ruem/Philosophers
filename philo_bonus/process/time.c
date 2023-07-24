/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:45:11 by cormiere          #+#    #+#             */
/*   Updated: 2023/07/23 11:51:01 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

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

// This function introduces a delay in milliseconds,
// while checking for the termination condition.
void	ft_usleep(t_data *data, long int time_in_ms)
{
	long int	start_time;

	start_time = get_time_from_start(data->time_start);
	while (get_time_from_start(data->time_start) < start_time + time_in_ms)
	{
		if (data->philo_dead == true)
			return ;
		usleep(time_in_ms / 20);
	}
}

// This function performs a usleep routine with a milliseconds duration.
void	ft_usleep_routine(t_data *data, t_philo *philo, long int time_in_ms)
{
	long int	start_time;

	start_time = get_time_from_start(data->time_start);
	while (get_time_from_start(data->time_start) < start_time + time_in_ms)
	{
		if (death(data, philo))
			return ;
		usleep(time_in_ms / 30);
	}
}
