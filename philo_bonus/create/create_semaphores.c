#include "../includes/philo_bonus.h"

// This function initializes the semaphores used for synchronization.
int	init_semaphores(t_data *data)
{
	sem_unlink("/fork_sem");
	sem_unlink("/writing_sem");
	sem_unlink("/time_sem");
	sem_unlink("/eat_sem");
	sem_unlink("/dead_sem");
	data->fork = sem_open("/fork_sem", O_CREAT, 0644, data->input.number_philo);
	if (data->fork == SEM_FAILED)
		return (error_msg(SEM_OPEN, 1));
	data->writing = sem_open("/writing_sem", O_CREAT, 0644, 1);
	if (data->writing == SEM_FAILED)
		return (error_msg(SEM_OPEN, 2));
	data->time = sem_open("/time_sem", O_CREAT, 0644, 1);
	if (data->time == SEM_FAILED)
		return (error_msg(SEM_OPEN, 3));
	data->eat = sem_open("/eat_sem", O_CREAT, 0644, 1);
	if (data->eat == SEM_FAILED)
		return (error_msg(SEM_OPEN, 4));
	data->dead = sem_open("/dead_sem", O_CREAT, 0644, 1);
	if (data->dead == SEM_FAILED)
		return (error_msg(SEM_OPEN, 4));
	return (0);
}

// This function closes and unlinks the semaphores used for synchronization.
void	destroy_semaphores(t_data *data)
{
	sem_close(data->writing);
	sem_unlink("/writing_sem");
	sem_close(data->fork);
	sem_unlink("/fork_sem");
	sem_close(data->time);
	sem_unlink("/time_sem");
	sem_close(data->eat);
	sem_unlink("/eat_sem");
	sem_close(data->dead);
	sem_unlink("/dead_sem");
}
