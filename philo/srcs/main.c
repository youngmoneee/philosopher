/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:06:55 by youngpar          #+#    #+#             */
/*   Updated: 2022/04/24 02:28:15 by youngpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	parse(int argc, char **argv, t_routine *routine)
{
	routine->philo_num = arg_toi(argv[1]);
	routine->time_to_die = arg_toi(argv[2]);
	routine->time_to_eat = arg_toi(argv[3]);
	routine->time_to_sleep = arg_toi(argv[4]);
	routine->exited = (t_tv *)0;
	if (argc == 6)
	{
		if (arg_toi(argv[5]) < 0)
			err_msg("Args Error\n");
		routine->at_least_eat = arg_toi(argv[5]);
	}
	else
		routine->at_least_eat = -1;
	if (routine->philo_num < 2 || routine->time_to_sleep < 0
		|| routine->time_to_eat < 0 || routine->time_to_die < 0)
		err_msg("Args Error\n");
}

int	main(int argc, char **argv)
{
	t_routine	routine;
	t_bool		flag;

	if (argc != 5 && argc != 6)
		err_msg("Arguments should be 4-5\n");
	parse(argc, argv, &routine);
	//bsleep(&routine.start, &now, 1000);
	// init printer
	pthread_mutex_init(&routine.print_right, NULL);

	// init ticket
	ticket_init(&routine);
	printf("ticket init success\n");
	// init forks
	forks_init(&routine);
	printf("fork init success\n");
	//	start time check
	gettimeofday(&routine.start, NULL);
	printf("================== Start ==================\n");
	// init philosopher
	flag = philo_init(&routine);
	printf("philo init success\n");

	//	philo status check

	//	join
	for (int i = 0; i < routine.philo_num; i++) {
		pthread_join(routine.philos[i].thread_id, NULL);
	}
	printf("join success\n");

	//	print release
	pthread_mutex_destroy(&routine.print_right);

	forks_destroy(&routine, routine.philo_num);
	printf("fork destroy success\n");
	ticket_destroy(&routine, (routine.philo_num + 1) / 2);
	printf("ticket destroy success\n");
	if (flag)
		return (flag);
	return (0);
}
