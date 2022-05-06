#include "../include/philo.h"

void	sleeping(t_philo *philo)
{
	print_status(SLEEPING, philo);
	release_forks(philo);
	if (philo->routine->exited == FALSE)
		bsleep(&philo->last, philo->routine->tteat + philo->routine->ttsleep);
	if (elapsed(&philo->last) > philo->routine->ttdie)
	{
		philo->routine->exited = TRUE;
		philo->routine->died = philo->no;
	}
	print_status(THINKING, philo);
}

void	eating(t_philo *philo)
{
	t_routine	*rtn;

	rtn = philo->routine;
	taken_forks(philo);
	//	Critical Section(Eating)
	philo->meal_cnt++;
	gettimeofday(&philo->last, NULL);
	print_status(EATING, philo);
	if (philo->routine->exited == FALSE)
		bsleep(&philo->last, rtn->tteat);
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
	gettimeofday(&now, NULL);
	if (philo->no & 1)
		bsleep(&now, rtn->tteat);
	while (rtn->exited == FALSE)
	{
		if (rtn->ttdie < elapsed(&philo->last))
		{
			rtn->exited = TRUE;
			rtn->died = philo->no;
		}
		if (rtn->exited == FALSE)
			eating(philo);
	}
	while (philo->no != rtn->join);
	return (NULL);
}
