/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:40:42 by youngpar          #+#    #+#             */
/*   Updated: 2022/04/13 20:40:43 by youngpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	err_msg(char *msg)
{
	while (*msg)
		write(2, msg++, 1);
	exit(0);
}

void	thread_exception_handler(t_routine *routine, int error_idx)
{
	while (++routine->join < error_idx)
	{
		gettimeofday(&routine->exited, NULL);
		if (routine->join < error_idx)
			pthread_join(routine->philos[routine->join].thread_id, NULL);
	}
	free(routine->philos);
}

int 	exiter(t_routine *routine)
{
	int		idx;
	int		meal_cnt;
	t_philo	*philo;
	t_tv	now;

	idx = 0;
	meal_cnt = 0;
	while (!routine->exited.tv_sec && idx < routine->philo_num)
	{
		philo = &routine->philos[idx];
		if (!philo)
			continue ;
		if (routine->at_least_eat != -1 && philo->meal_cnt >= routine->at_least_eat)
			meal_cnt++;
		if (!routine->exited.tv_sec && routine->time_to_die \
				< get_elapsed_ms(&philo->last_meal, &now))
		{
			gettimeofday(&routine->exited, NULL);
			routine->died = idx;
		}
		idx++;
	}
	return (meal_cnt);
}

void	*dead_checker(t_routine *routine)
{
	while (!routine->exited.tv_sec)
	{
		if (exiter(routine) == routine->philo_num)
			gettimeofday(&routine->exited, NULL);
		usleep(1000);
	}
	return (NULL);
}