/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:44:54 by cormiere          #+#    #+#             */
/*   Updated: 2023/07/23 11:45:25 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

// This function displays an error message and returns a specified return value.
int	error_msg(char *s1, int ret_val)
{
	if (s1)
	{
		write(STDERR_FILENO, s1, ft_strlen(s1));
		write(STDERR_FILENO, "\n", 1);
	}
	return (ret_val);
}

// This function prints an action performed by a philosopher.
int	print_philo_action(t_philo *philo, t_data *data, char *action)
{
	if (death(data, philo))
		return (1);
	sem_wait(data->writing);
	printf("%lld	%d%s", get_time_from_start(data->time_start),
		philo->pos + 1, action);
	sem_post(data->writing);
	return (0);
}
