/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:06:55 by youngpar          #+#    #+#             */
/*   Updated: 2022/05/06 18:07:57 by youngpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	parse(int argc, char **argv, t_routine *routine)
{
	routine->philo_num = arg_toi(argv[1]);
	routine->ttdie = arg_toi(argv[2]);
	routine->tteat = arg_toi(argv[3]);
	routine->ttsleep = arg_toi(argv[4]);
	routine->exited = FALSE;
	routine->died = -1;
	routine->join = -1;
	if (argc == 6)
	{
		if (arg_toi(argv[5]) < 0)
			err_msg("Args Error\n");
		routine->must = arg_toi(argv[5]);
	}
	else
		routine->must = -1;
	if (routine->philo_num < 1 || routine->ttsleep < 0
		|| routine->tteat < 0 || routine->ttdie < 0)
		err_msg("Args Error\n");
}

int	main(int argc, char **argv)
{
	t_routine	routine;

	if (argc != 5 && argc != 6)
		err_msg("Arguments should be 4-5\n");
	parse(argc, argv, &routine);
	gettimeofday(&routine.start, NULL);
	initialize(&routine);
	dead_checker(&routine);
	forks_destroy(&routine, routine.philo_num);
	ticket_destroy(&routine, (routine.philo_num + 1) / 2);
	pthread_mutex_destroy(&routine.print_right);
	//system("leaks philo");
	return (0);
}
