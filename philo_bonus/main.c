#include "includes/philo_bonus.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av))
		return (1);
	if (create_data(&data, ac, av))
		return (2);
	if (init_semaphores(&data))
		return (3);
	if (data.input.number_philo == 1)
		return (single_philo(&data), 0);
	if (create_childs(&data))
		return (destroy_semaphores(&data), 4);
	destroy_semaphores(&data);
	return (0);
}
