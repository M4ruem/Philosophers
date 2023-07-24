/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:45:08 by cormiere          #+#    #+#             */
/*   Updated: 2023/07/23 11:51:36 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// This function represents the behavior of a child process.
int	child(t_data *data, t_philo *philo)
{
	while (!death(data, philo) \
		&& (!data->input.number_meal || \
		philo->meal_count < data->input.number_meal))
	{
		if (life_cycle(data, philo))
		{
			usleep(1000);
			destroy_semaphores(data);
			exit (1);
		}
	}
	if (death(data, philo))
	{
		usleep(1000);
		destroy_semaphores(data);
		exit (1);
	}
	pthread_detach(philo->thread);
	destroy_semaphores(data);
	exit (0);
}

// This function checks if a philosopher should die.
int	death(t_data *data, t_philo *philo)
{
	long long	time;

	sem_wait(data->time);
	time = get_time_from_start(philo->time_until_die);
	sem_post(data->time);
	sem_wait(data->dead);
	if (data->philo_dead == true)
		return (sem_post(data->dead), 1);
	sem_post(data->dead);
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
	return (0);
}

// This function represents the life cycle of a philosopher.
int	life_cycle(t_data *data, t_philo *philo)
{
	if (pthread_create(&philo->thread, NULL, check_dead, philo))
		return (error_msg(TCREAT, 2));
	if (death(data, philo))
		return (pthread_detach(philo->thread), 1);
	if (eating(data, philo))
		return (pthread_detach(philo->thread), 3);
	if (death(data, philo))
		return (pthread_detach(philo->thread), 1);
	if (sleeping(data, philo))
		return (pthread_detach(philo->thread), 4);
	if (death(data, philo))
		return (pthread_detach(philo->thread), 1);
	if (thinking(data, philo))
		return (pthread_detach(philo->thread), 5);
	if (death(data, philo))
		return (pthread_detach(philo->thread), 1);
	pthread_detach(philo->thread);
	return (0);
}

// This function simulates the behavior of a single philosopher.
void	single_philo(t_data *data)
{
	data->pid[0] = fork();
	if (data->pid[0] == 0)
	{
		data->time_start = get_time();
		printf("0	1%s", TAKEN_FORK);
		ft_usleep(data, data->input.to_die);
		printf("%ld	1%s", data->input.to_die, PHILO_DIED);
	}
	waitpid(data->pid[0], NULL, 0);
	destroy_semaphores(data);
}
