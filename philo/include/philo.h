/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 20:40:48 by youngpar          #+#    #+#             */
/*   Updated: 2022/04/24 02:28:18 by youngpar         ###   ########.fr       */
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

# define TIME_STAMP		"%d_in_ms "
# define TAKEN_FORK		"%d has taken a fork\n"
# define EATING			"%d is eating\n"
# define THINKING		"%d is thinking\n"
# define SLEEPING		"%d is sleeping\n"
# define DIED			"%d is died\n"

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
	int 	philo_num;
	int 	time_to_die;
	int 	time_to_eat;
	int 	time_to_sleep;
	int 	at_least_eat;
	t_tv 	*exited;
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
	t_tv		last_meal;
	t_routine	*routine;
	pthread_t 	thread_id;
};

/*
 * Exceptions
 */

void	err_msg(char *msg);
void	thread_exception_handler(t_routine *routine, int error_idx);
void	ticket_destroy(t_routine *routine, int size);
void	forks_destroy(t_routine *routine, int size);

/*
 * Util
 */

t_bool	is_space(char c);
int 	arg_toi(char *s);
int		get_elapsed_ms(t_tv *std_time, t_tv *cur_time);
void	bsleep(t_tv *start, t_tv *now, int ms);
t_bool	print_status(char *msg, t_philo *philo);


/*
 * Init
 */

t_bool	philo_init(t_routine *routine);
t_bool	ticket_init(t_routine *routine);
t_bool	forks_init(t_routine *routine);


/*
 * Philosopher
 */

void	*life(void *philosopher);
void	eating(t_philo *philo);

#endif //PHILO_H
