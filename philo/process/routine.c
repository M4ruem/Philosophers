/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:44:14 by cormiere          #+#    #+#             */
/*   Updated: 2023/07/24 15:05:36 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// This function checks if the program should stop or terminate.
int	check(t_data *data)
{
	pthread_mutex_lock(&data->stop);
	if (data->philo_dead)
	{
		pthread_mutex_unlock(&data->stop);
		return (1);
	}
	pthread_mutex_unlock(&data->stop);
	return (0);
}

// This function represents the routine or life cycle of a philosopher.
void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	*memory;

	philo = (t_philo *)arg;
	memory = philo->memory;
	// if (memory->input.number_philo == 1)
	// {
	// 	single_philo(arg);
	// 	exit (0);
	// }
	if (memory->input.number_meal)
	{
		while (!check(memory)
			&& philo->meal_count
			< memory->input.number_meal)
			if (life_cycle(philo, memory))
				return (NULL);
	}
	else
	{
		while (!check(memory))
			if (life_cycle(philo, memory))
				return (NULL);
	}
	return (NULL);
}

// This function represents a single iteration of a philosopher's life cycle.
int	life_cycle(t_philo *philo, t_data *data)
{
	if (check(data))
		return (1);
	if (fork_init_eating(philo, philo->memory))
		return (2);
	if (check(data))
		return (1);
	if (sleeping(philo, philo->memory))
		return (3);
	if (check(data))
		return (1);
	if (thinking(philo, philo->memory))
		return (4);
	if (check(data))
		return (1);
	return (0);
}

// This function represents the life cycle of a single philosopher
// in a scenario where there's only one philosopher.
// void	single_philo(t_data *data)
// {
// 	data->time_start = get_time();
// 	printf("0	1%s", TAKEN_FORK);
// 	// pthread_mutex_lock(data->philo->right_fork);
// 	// print_philo_action(data->philo, data, TAKEN_FORK);
// 	// pthread_mutex_unlock(data->philo->right_fork);
// 	ft_usleep(data, data->input.to_die);
// 	printf("%ld	1%s", data->input.to_die, PHILO_DIED);
// }
