#include "../includes/philo.h"

void	ft_take_fork(t_ph *ph)
{
	sem_wait(ph->all->forks);
	ft_print_mes(ph, "%lu: %d has taken a fork\n");
	sem_wait(ph->all->forks);
	ft_print_mes(ph, "%lu: %d has taken a fork\n");
}

void	ft_free_fork(t_ph *ph)
{
	sem_post(ph->all->forks);
	sem_post(ph->all->forks);
}

void	ft_output(char *s, t_data *data, int i)
{
	sem_wait(data->print);
	printf(s, ft_get_time(data), i);
	sem_post(data->died);
	sem_wait(data->the_end);
}

void	ft_print_mes(t_ph *ph, char *s)
{
	sem_wait(ph->all->print);
	printf(s, ft_get_time(ph->all), ph->id);
	sem_post(ph->all->print);
}

int	ft_usleep(unsigned long msec, t_data *data)
{
	unsigned long	stop;
	unsigned long	new_start;

	stop = ft_get_time(data) + msec;
	new_start = ft_get_time(data);
	while (new_start < stop)
	{
		usleep (100);
		new_start = ft_get_time(data);
	}
	return (0);
}
