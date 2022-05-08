/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:40:48 by youngpar          #+#    #+#             */
/*   Updated: 2022/05/06 17:03:45 by youngpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

/*
 * Philosopher
 */

# define TRUE			1
# define FALSE			0
# define INIT_SUCCESS	0
# define INIT_FAILED	1

/*
 * Philosopher Message Interface
 */

# define TIME_STAMP		"%d "
# define TAKEN_FORK		"%d %d has taken a fork\n"
# define EATING			"%d %d is eating\n"
# define THINKING		"%d %d is thinking\n"
# define SLEEPING		"%d %d is sleeping\n"
# define DIED			"%d %d is died\n"

/*
 * Type define
 */

typedef int 				t_bool;
typedef struct s_philo		t_philo;
typedef struct s_routine	t_routine;
typedef long long			t_ll;
typedef unsigned long long	t_ull;
typedef struct timeval		t_tv;
typedef pthread_mutex_t		t_mtx;

struct s_routine
{
	int 	num;
	int 	ttdie;
	int 	tteat;
	int 	ttsleep;
	int 	must;
	int 	died;
	int 	join;
	t_bool 	exited;
	t_tv	start;
	t_philo *philos;
	t_mtx	*ticket;
	t_mtx	*forks;
	t_mtx	print_right;
};

struct s_philo
{
	int			no;
	int			meal_cnt;
	t_tv		last;
	t_routine	*routine;
	pthread_t 	thread_id;
};

/*
 * Exceptions
 */

void	err_msg(char *msg);
void	thread_exception_handler(t_routine *routine, int error_idx);
void	dead_checker(t_routine *routine);
int 	exiter(t_routine *routine);


/*
 * Util
 */

t_bool	is_space(char c);
int 	arg_toi(char *s);
int 	elapsed(t_tv *standard);
void	bsleep(t_tv *start, int ms);
t_bool	print_status(char *msg, t_philo *philo);


/*
 * Init
 */

t_bool	thread_init(t_routine *routine);
t_bool	philo_init(t_routine *routine);
t_bool	ticket_init(t_routine *routine);
t_bool	forks_init(t_routine *routine);
void	initialize(t_routine *routine);

/*
 * Philosopher
 */

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	*life(void *philosopher);


/*
 * Mutex
 */
void	taken_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	ticket_destroy(t_routine *routine, int size);
void	forks_destroy(t_routine *routine, int size);

#endif //PHILO_H
