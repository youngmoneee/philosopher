/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:40:42 by youngpar          #+#    #+#             */
/*   Updated: 2022/05/18 00:01:44 by youngpar         ###   ########.fr       */
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
	if (routine->died != -1)
		printf(DIED, elapsed(&routine->start), routine->died + 1);
	while (++(routine->join) < error_idx)
		pthread_join(routine->philos[routine->join].thread_id, NULL);
	free(routine->philos);
}

int	exiter(t_routine *routine)
{
	int		idx;
	int		meal_cnt;
	t_philo	*philo;

	idx = 0;
	meal_cnt = 0;
	while (routine->exited == FALSE && idx < routine->num)
	{
		philo = &routine->philos[idx];
		if (routine->must != -1 && philo->meal_cnt >= routine->must)
			meal_cnt++;
		if (routine->exited == FALSE && routine->ttdie < elapsed(&philo->last))
		{
			routine->exited = TRUE;
			routine->died = idx;
		}
		idx++;
	}
	return (meal_cnt);
}

void	dead_checker(t_routine *routine)
{
	while (routine->exited == FALSE)
	{
		if (exiter(routine) == routine->num)
		{
			routine->exited = TRUE;
			thread_exception_handler(routine, routine->num);
			return ;
		}
		usleep(300);
	}
	thread_exception_handler(routine, routine->num);
}
