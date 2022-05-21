/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:01:57 by youngpar          #+#    #+#             */
/*   Updated: 2022/05/18 00:12:08 by youngpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	taken_forks(t_philo *philo)
{
	t_routine	*rtn;

	rtn = philo->routine;
	if (rtn->exited)
		return ;
	pthread_mutex_lock(&rtn->forks[philo->no]);
	print_status(TAKEN_FORK, philo);
	if (&rtn->forks[(philo->no + 1) % rtn->num] == &rtn->forks[philo->no])
	{
		pthread_mutex_unlock(&rtn->forks[philo->no]);
		while (TRUE)
			if (rtn->exited)
				break ;
		return ;
	}
	pthread_mutex_lock(&rtn->forks[(philo->no + 1) % rtn->num]);
	print_status(TAKEN_FORK, philo);
}

void	release_forks(t_philo *philo)
{
	t_routine	*rtn;

	rtn = philo->routine;
	pthread_mutex_unlock(&rtn->forks[philo->no]);
	pthread_mutex_unlock(&rtn->forks[(philo->no + 1) % rtn->num]);
}

void	forks_destroy(t_routine *routine, int size)
{
	int	idx;

	idx = 0;
	while (idx < size)
	{
		pthread_mutex_destroy(&routine->forks[idx]);
		idx++;
	}
	free(routine->forks);
}
