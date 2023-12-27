#include "philo.h"

int	ft_atoi(const char *str)
{
	int	res;
	int	q;

	res = 0;
	q = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-')
	{
		q++;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	if (q == 1)
		res *= -1;
	return (res);
}

long long	get_time_in_ms(void)
{
	struct timeval			tv;
	static long long int	start;
	static int count;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	if (count != 1)
	{
		start = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
		count = 1;
	}
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - start);
}

long long	my_usleep(int time)
{
	int	i;

	i = 0;
	long long a = get_time_in_ms();
	while (get_time_in_ms() - a < time)
		;
	return i;
}