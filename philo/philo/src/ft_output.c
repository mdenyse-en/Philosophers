#include "../includes/philo.h"

void	ft_take_fork(t_ph *ph)
{
	if (ph->id % 2)
		pthread_mutex_lock(&ph->all->forks[ph->id - 1]);
	else
		pthread_mutex_lock(&ph->all->forks[ph->id - 2]);
	ft_print_mes(ph, "%lu: %d has taken a fork\n");
	if (ph->id % 2)
	{
		if (ph->id == ph->all->count_ph)
			pthread_mutex_lock(&ph->all->forks[0]);
		else
			pthread_mutex_lock(&ph->all->forks[ph->id]);
	}
	else
		pthread_mutex_lock(&ph->all->forks[ph->id - 1]);
	ft_print_mes(ph, "%lu: %d has taken a fork\n");
}

void	ft_free_fork(t_ph *ph)
{
	if (ph->id % 2)
	{
		if (ph->id == ph->all->count_ph)
			pthread_mutex_unlock(&ph->all->forks[0]);
		else
			pthread_mutex_unlock(&ph->all->forks[ph->id]);
		pthread_mutex_unlock(&ph->all->forks[ph->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&ph->all->forks[ph->id - 1]);
		pthread_mutex_unlock(&ph->all->forks[ph->id - 2]);
	}
}

void	ft_output(char *s, t_data *data, int i)
{
	pthread_mutex_lock(&data->print);
	printf(s, ft_get_time(data), i + 1);
	pthread_mutex_lock(&data->the_end);
}

void	ft_print_mes(t_ph *ph, char *s)
{
	pthread_mutex_lock(&ph->all->print);
	printf(s, ft_get_time(ph->all), ph->id);
	pthread_mutex_unlock(&ph->all->print);
}
