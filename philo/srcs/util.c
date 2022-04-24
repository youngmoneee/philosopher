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

int 	arg_toi(char *s)
{
	t_ll 	ret;

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

int get_elapsed_ms(t_tv *std_time, t_tv *cur_time)
{
	int ret;

	ret = (cur_time->tv_sec - std_time->tv_sec) * 1000;
	ret += (cur_time->tv_usec - std_time->tv_usec) / 1000;

	return (ret);
}

void bsleep(t_tv *start, t_tv *now, int ms)
{
	int elapsed;

	gettimeofday(now, NULL);
	elapsed = get_elapsed_ms(start, now);
	//printf("current Elapsed Time is %d\n", elapsed);
	if (elapsed >= ms)
		return ;
	usleep((ms - elapsed) / 2 * 1000 + 100);
	bsleep(start, now, ms);
}

//void	timestamp()
