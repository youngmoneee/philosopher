#include "../include/philo.h"

void	taken_forks(t_philo *philo)
{
	t_routine	*rtn;

	rtn = philo->routine;
	if (philo->routine->exited)
		return ;
	pthread_mutex_lock(&rtn->ticket[philo->no / 2]);
	pthread_mutex_lock(&rtn->forks[philo->no]);
	print_status(TAKEN_FORK, philo);
	pthread_mutex_lock(&rtn->forks[(philo->no + 1) % rtn->philo_num]);
	print_status(TAKEN_FORK, philo);
}

void	release_forks(t_philo *philo)
{
	t_routine	*rtn;

	rtn = philo->routine;
	if (philo->routine->exited)
		return ;
	pthread_mutex_unlock(&rtn->forks[philo->no + 1 % rtn->philo_num]);
	pthread_mutex_unlock(&rtn->forks[philo->no]);
	pthread_mutex_unlock(&rtn->ticket[philo->no / 2]);
}

void	ticket_destroy(t_routine *routine, int size)
{
	int idx;

	idx = 0;
	while (idx < size)
	{
		pthread_mutex_destroy(&routine->ticket[idx]);
		idx++;
	}
	free(routine->ticket);
}

void	forks_destroy(t_routine *routine, int size)
{
	int idx;

	idx = 0;
	while (idx < size)
	{
		pthread_mutex_destroy(&routine->forks[idx]);
		idx++;
	}
	free(routine->forks);
}
