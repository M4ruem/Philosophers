/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:44:26 by cormiere          #+#    #+#             */
/*   Updated: 2023/07/24 14:55:46 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	pthread_t single_philo_thread;

	if (parsing(ac, av))
		return (1);
	if (create_data(&data, ac, av))
		return (2);
	if (data.input.number_philo == 1) {
		if(pthread_create(&single_philo_thread, NULL, single_philo, &data) != 0) {
			perror("Thread creation failed");
			return 1;
		}
		if(pthread_join(single_philo_thread, NULL) != 0) {
			perror("Failed to join thread");
			return 1;
		}
	 	return 0;
	}
	if (create_threads(&data))
		return (3);
	destroy_mutexes(&data, data.input.number_philo);
	return (0);
}