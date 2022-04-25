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
	int idx;

	idx = 0;
	gettimeofday(routine->exited, NULL);
	while (idx < error_idx)
	{
		pthread_join(routine->philos[idx].thread_id, NULL);
	}
	free(routine->philos);
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