#include "../include/philo.h"

void	eating(t_philo *philo)
{
	t_routine	*rtn;

	rtn = philo->routine;
	pthread_mutex_lock(&rtn->ticket[philo->no / 2]);
	pthread_mutex_lock(&rtn->forks[philo->no]);
	pthread_mutex_lock(&rtn->forks[philo->no + 1 % rtn->philo_num]);
	//	Critical Section(Eating)
	print_status(TAKEN_FORK, philo);
	bsleep(&rtn->start, &philo->last_meal, rtn->time_to_eat);
	print_status(EATING, philo);
	//	End Section
	pthread_mutex_unlock(&rtn->forks[philo->no + 1 % rtn->philo_num]);
	pthread_mutex_unlock(&rtn->forks[philo->no]);
	pthread_mutex_unlock(&rtn->ticket[philo->no / 2]);
}

void	*life(void *philosopher)
{
	t_philo	*philo;
	t_tv	now;
	int 	time;

	philo = (t_philo *)philosopher;
	philo->last_meal = philo->routine->start;
	//printf("%ld %d\n", philo->last_meal.tv_sec, philo->last_meal.tv_usec);
	while (!philo->routine->exited)
	{
		gettimeofday(&now, NULL);
		time = get_elapsed_ms(&philo->last_meal, &now);
		if (time >= philo->routine->time_to_die)
		{
			philo->routine->exited = &now;
			break ;
		}
		eating(philo);
		print_status(SLEEPING, philo);
		bsleep(&philo->last_meal, &now, philo->routine->time_to_sleep);
		print_status(THINKING, philo);
	}
	return (NULL);
}