/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cormiere <cormiere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 11:44:00 by cormiere          #+#    #+#             */
/*   Updated: 2023/07/23 11:46:17 by cormiere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// This function checks if a given string
// represents a valid number.
int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i])
		return (1);
	return (0);
}

// This function checks if the command-line
// arguments represent valid positive integers.
int	is_positive(int ac, char **av)
{
	int		i;
	long	res;

	i = 1;
	while (i < ac)
	{
		if (!av[i][0])
			return (error_msg(INT, 1));
		if (is_num(av[i]))
			return (error_msg(NUMBER, 1));
		res = ft_atoi(av[i]);
		if (res < 0 || res > 2147483647)
			return (error_msg(INT, 1));
		i++;
	}
	return (0);
}

// This function performs the initial command-line
// argument parsing and validation.
int	parsing(int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (error_msg(TUTO, 1));
	if (ft_atoi(av[1]) <= 0 || ft_atoi(av[1]) > 200)
		return (error_msg(N_PHILO, 2));
	if (is_positive(ac, av))
		return (3);
	return (0);
}
