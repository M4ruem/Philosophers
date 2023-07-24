/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:45:00 by cormiere          #+#    #+#             */
/*   Updated: 2023/07/23 11:45:25 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// This function represents the eating action of a philosopher.
int	eating(t_data *data, t_philo *philo)
{
	sem_wait(data->fork);
	if (print_philo_action(philo, data, TAKEN_FORK))
		return (1);
	sem_wait(data->fork);
	if (print_philo_action(philo, data, TAKEN_FORK))
		return (1);
	if (print_philo_action(philo, data, EATING))
		return (1);
	sem_wait(data->time);
	philo->time_until_die = get_time();
	sem_post(data->time);
	ft_usleep_routine(data, philo, data->input.to_eat);
	sem_post(data->fork);
	sem_post(data->fork);
	sem_wait(data->eat);
	philo->meal_count++;
	sem_post(data->eat);
	return (0);
}

// This function represents the sleeping action of a philosopher.
int	sleeping(t_data *data, t_philo *philo)
{
	if (print_philo_action(philo, data, SLEEPING))
		return (1);
	ft_usleep_routine(data, philo, data->input.to_sleep);
	return (0);
}

// This function represents the thinking action of a philosopher.
int	thinking(t_data *data, t_philo *philo)
{
	if (print_philo_action(philo, data, THINKING))
		return (1);
	return (0);
}
