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

//void	timestamp()
