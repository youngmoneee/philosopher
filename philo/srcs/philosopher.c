#include "../include/philo.h"

void	sleeping(t_philo *philo)
{
	t_tv	start;

	gettimeofday(&start, NULL);
	print_status(SLEEPING, philo);
	release_forks(philo);
	bsleep(&start, &philo->last_sleep, philo->routine->time_to_sleep);
	if (get_elapsed_ms(&philo->last_meal, &start) > philo->routine->time_to_die)
		gettimeofday(&philo->routine->exited, NULL);
	print_status(THINKING, philo);
}

void	eating(t_philo *philo)
{
	t_routine	*rtn;
	t_tv		now;

	rtn = philo->routine;
	taken_forks(philo);
	//	Critical Section(Eating)
	philo->meal_cnt++;
	gettimeofday(&philo->last_meal, NULL);
	print_status(EATING, philo);
	bsleep(&philo->last_meal, &now, rtn->time_to_eat);
	//	End Section
	sleeping(philo);
}

void	*life(void *philosopher)
{
	t_philo		*philo;
	t_routine	*rtn;
	t_tv		now;

	philo = (t_philo *)philosopher;
	rtn = philo->routine;
	philo->last_meal = rtn->start;
	while (!rtn->exited.tv_sec)
	{
		if (rtn->time_to_die < get_elapsed_ms(&philo->last_meal, &now))
		{
			gettimeofday(&rtn->exited, NULL);
			rtn->died = philo->no;
		}
		if (!rtn->exited.tv_sec)
			eating(philo);
	}
	while (rtn->join != philo->no);
	return (NULL);
}