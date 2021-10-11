#include "../includes/philo.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(char *num)
{
	int	res;

	res = 0;
	while (*num != '\0' && (*num >= '0' && *num <= '9'))
		res = res * 10 + *num++ - '0';
	return (res);
}

unsigned long	ft_get_time(t_data *data)
{
	unsigned long	msec;
	struct timeval	time;

	sem_wait(data->the_end);
	gettimeofday(&time, NULL);
	msec = (time.tv_sec - data->st_time.tv_sec) * 1000
		+ (time.tv_usec - data->st_time.tv_usec) / 1000;
	sem_post(data->the_end);
	return (msec);
}

int	ft_get_dif_eat(t_ph *ph)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((int)((time.tv_sec - ph->t_last_eat.tv_sec) * 1000
		+ (time.tv_usec - ph->t_last_eat.tv_usec) / 1000));
}
