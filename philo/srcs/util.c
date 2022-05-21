/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngpar <youngseo321@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 00:00:07 by youngpar          #+#    #+#             */
/*   Updated: 2022/05/18 00:01:28 by youngpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_bool	is_space(char c)
{
	if (c == 0x20
		|| c == 0x09
		|| c == 0x0A
		|| c == 0x0B
		|| c == 0x0C
		|| c == 0x0D)
		return (TRUE);
	return (FALSE);
}

int	arg_toi(char *s)
{
	t_ll	ret;

	ret = 0;
	while (is_space(*s) && *s)
		s++;
	if (!*s)
		return (-1);
	if (*s == '+' || *s == '-')
		if (*s++ == '-')
			return (-1);
	while (*s >= '0' && *s <= '9')
	{
		ret = ret * 10 + *s - '0';
		if (ret >= 2147483647)
			return (-1);
		s++;
	}
	return ((int)ret);
}

int	elapsed(t_tv *standard)
{
	int		ret;
	t_tv	now;

	gettimeofday(&now, NULL);
	ret = (now.tv_sec - standard->tv_sec) * 1000;
	ret += ((now.tv_usec - standard->tv_usec) / 1000);
	return (ret);
}

void	bsleep(t_tv *start, int ms)
{
	int		time;

	time = elapsed(start);
	if (time >= ms)
		return ;
	usleep((ms - time) * 1000 / 2 + 100);
	bsleep(start, ms);
}

t_bool	print_status(char *msg, t_philo *philo)
{
	if (philo->routine->exited == TRUE)
		return (FALSE);
	pthread_mutex_lock(&philo->routine->print_right);
	if (philo->routine->exited)
	{
		pthread_mutex_unlock(&philo->routine->print_right);
		return (FALSE);
	}
	printf(msg, elapsed(&philo->routine->start), philo->no + 1);
	pthread_mutex_unlock(&philo->routine->print_right);
	return (TRUE);
}
