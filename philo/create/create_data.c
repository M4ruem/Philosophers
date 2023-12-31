/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:43:42 by cormiere          #+#    #+#             */
/*   Updated: 2023/07/23 11:47:03 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// This function initializes the shared data structure.
int	create_data(t_data *data, int ac, char **av)
{
	data->philo_dead = 0;
	data->time_start = 0;
	init_input(&data->input, ac, av);
	init_philo(data);
	if (init_mutex(data))
		return (1);
	return (0);
}

// This function initializes the input parameters of the program.
void	init_input(t_input *input, int ac, char **av)
{
	input->number_philo = ft_atoi(av[1]);
	input->to_die = ft_atoi(av[2]);
	input->to_eat = ft_atoi(av[3]);
	input->to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		input->number_meal = ft_atoi(av[5]);
	else
		input->number_meal = 0;
}

// This function initializes the philosophers data structures.
void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input.number_philo)
	{
		data->philo[i].meal_count = 0;
		data->philo[i].memory = 0;
		data->philo[i].pos = i;
		data->philo[i].time_until_die = 0;
		data->philo[i].thread = 0;
		data->philo[i].memory = data;
		i++;
	}
}
