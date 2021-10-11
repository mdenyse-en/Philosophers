#include "../includes/philo.h"

void	*ft_control_death(void *philos)
{
	int				i;
	t_ph			*ph;

	ph = (t_ph *)philos;
	while (1)
	{
		i = -1;
		if (ft_get_dif_eat(ph) > ph->all->t_die)
			ft_output("%lu: %d died\n", ph->all, ph->id);
		usleep(100);
	}
}

void	*ft_control_count(void *d)
{
	t_data	*data;
	int		i;

	data = (t_data *)d;
	i = -1;
	while (++i < data->count_ph)
		sem_wait(data->ph[i].eat_c_monitor);
	ft_output("%lu: all philosofers eated %d times\n", data, data->eat_end);
	return ((void *)0);
}

void	ft_sems_unlinks(void)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("the_end");
	sem_unlink("died");
	sem_unlink("eat_monitor");
}
