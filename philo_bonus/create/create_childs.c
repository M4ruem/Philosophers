#include "../includes/philo_bonus.h"

// This function kills child processes.
int	kill_child_process(t_data *data, int until)
{
	int	i;

	i = 0;
	while (i < until)
	{
		usleep(100);
		kill(data->pid[i], SIGKILL);
		i += 2;
		if (i > until && i % 2 == 0)
			i = 1;
	}
	return (0);
}

// This function waits for all child processes to terminate.
int	wait_all_child(t_data *data)
{
	int	i;
	int	status;

	i = -1;
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) == 1)
	{
		while (++i < data->input.number_philo)
			kill(data->pid[i], SIGKILL);
		return (0);
	}
	i = 0;
	while (i < data->input.number_philo)
	{
		waitpid(data->pid[i], &status, 0);
		i++;
	}
	return (0);
}

// This function creates child processes and manages their execution.
int	create_childs(t_data *data)
{
	int		i;

	i = 0;
	data->time_start = get_time();
	while (i < data->input.number_philo)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			return (error_msg(FORK, 1), kill_child_process(data, i), 1);
		if (data->pid[i] == 0)
			child(data, &data->philo[i]);
		i += 2;
		if (i >= data->input.number_philo && i % 2 == 0)
		{
			i = 1;
			if (data->input.to_eat < data->input.to_die)
				ft_usleep(data, data->input.to_eat);
			else
				ft_usleep(data, data->input.to_die / 2);
		}
	}
	wait_all_child(data);
	return (0);
}
