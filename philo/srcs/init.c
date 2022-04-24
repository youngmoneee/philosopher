#include "../include/philo.h"

t_bool	philo_init(t_routine *routine)
{
	int idx;

	idx = 0;
	routine->philos = (t_philo *)malloc(sizeof(t_philo) * routine->philo_num);
	if (!(routine->philos))
		return (FALSE);
	while (idx < routine->philo_num)
	{
		routine->philos[idx].no = idx;
		&routine->philos[idx].routine = routine;
		routine->philos[idx].meal_cnt = 0;
		idx++;
	}
}