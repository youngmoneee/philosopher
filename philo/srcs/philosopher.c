/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:07:13 by youngpar          #+#    #+#             */
/*   Updated: 2022/05/18 00:08:36 by youngpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	philo->meal_cnt++;
	gettimeofday(&philo->last, NULL);
	print_status(EATING, philo);
	if (philo->routine->exited == FALSE)
		bsleep(&philo->last, rtn->tteat);
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
	while (TRUE)
		if (philo->no == rtn->join)
			break ;
	return (NULL);
}
