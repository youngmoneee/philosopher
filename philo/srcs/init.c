/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:01:51 by youngpar          #+#    #+#             */
/*   Updated: 2022/05/18 00:13:12 by youngpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_bool	thread_init(t_routine *routine)
{
	int		idx;
	t_philo	*philo;
	t_bool	err;

	idx = 0;
	while (idx < routine->num)
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
	int		idx;
	t_philo	*philo;

	idx = 0;
	routine->philos = (t_philo *)malloc(sizeof(t_philo) * routine->num);
	if (!(routine->philos))
		return (FALSE);
	while (idx < routine->num)
	{
		philo = &routine->philos[idx];
		philo->no = idx;
		philo->routine = routine;
		philo->meal_cnt = 0;
		philo->last.tv_sec = routine->start.tv_sec;
		philo->last.tv_usec = routine->start.tv_usec;
		idx++;
	}
	return (TRUE);
}

t_bool	forks_init(t_routine *routine)
{
	int		idx;
	int		size;
	t_bool	flag;

	idx = 0;
	size = routine->num;
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
	forks_init(routine);
	philo_init(routine);
	thread_init(routine);
}
