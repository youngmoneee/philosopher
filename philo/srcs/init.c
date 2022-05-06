#include "../include/philo.h"

t_bool	thread_init(t_routine *routine)
{
	int		idx;
	t_philo	*philo;
	t_bool	err;

	idx = 0;
	while (idx < routine->philo_num)
	{
		philo = &routine->philos[idx];
		err = pthread_create(&philo->thread_id, NULL, life, (void *)philo);
		if (err)
		{
			thread_exception_handler(routine, idx);
			return (FALSE);
		}
		idx++;
	}
	return (TRUE);
}

t_bool	philo_init(t_routine *routine)
{
	int idx;
	t_philo	*philo;

	idx = 0;
	routine->philos = (t_philo *)malloc(sizeof(t_philo) * routine->philo_num);
	if (!(routine->philos))
		return (FALSE);
	while (idx < routine->philo_num)
	{
		philo = &routine->philos[idx];
		philo->no = idx;
		philo->routine = routine;
		philo->meal_cnt = 0;
		philo->last = routine->start;
		idx++;
	}
	return (TRUE);
}

t_bool	ticket_init(t_routine *routine)
{
	int 	idx;
	int		size;
	t_bool	flag;

	idx = 0;
	size = (routine->philo_num + 1) / 2;
	routine->ticket = (t_mtx *)malloc(sizeof(t_mtx) * size);
	if (!routine->ticket)
		return (FALSE);
	while (idx < size)
	{
		flag = pthread_mutex_init(&routine->ticket[idx], NULL);
		if (flag)
		{
			ticket_destroy(routine, idx);
			return (FALSE);
		}
		idx++;
	}
	return (TRUE);
}

t_bool	forks_init(t_routine *routine)
{
	int 	idx;
	int		size;
	t_bool	flag;

	idx = 0;
	size = routine->philo_num;
	routine->forks = (t_mtx *)malloc(sizeof(t_mtx) * size);
	if (!routine->forks)
		return (FALSE);
	while (idx < size)
	{
		flag = pthread_mutex_init(&routine->forks[idx], NULL);
		if (flag)
		{
			forks_destroy(routine, idx);
			return (FALSE);
		}
		idx++;
	}
	return (TRUE);
}

void	initialize(t_routine *routine)
{
	pthread_mutex_init(&routine->print_right, NULL);
	ticket_init(routine);
	forks_init(routine);
	//pthread_create(&routine->checker, NULL, (void *)dead_checker, &routine);
	philo_init(routine);
	thread_init(routine);
}
