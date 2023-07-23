#include "includes/philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av))
		return (1);
	if (create_data(&data, ac, av))
		return (2);
	if (data.input.number_philo == 1)
		return (single_philo(&data), 0);
	if (create_threads(&data))
		return (3);
	destroy_mutexes(&data, data.input.number_philo);
	return (0);
}
