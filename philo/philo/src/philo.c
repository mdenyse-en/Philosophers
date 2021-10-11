#include "../includes/philo.h"

int	ft_usleep(unsigned long msec, t_data *data)
{
	unsigned long	stop;
	unsigned long	new_start;

	stop = ft_get_time(data) + msec;
	new_start = ft_get_time(data);
	while (new_start < stop)
	{
		usleep (10);
		new_start = ft_get_time(data);
	}
	return (0);
}

void	*ft_philo_live(void *t)
{
	t_ph	*ph;

	ph = t;
	while (1)
	{
		ft_take_fork(ph);
		ph->t_last_eat = ft_get_time(ph->all);
		ft_print_mes(ph, "%lu: %d is eating\n");
		ph->eat_count++;
		ft_usleep(ph->all->t_eat, ph->all);
		ft_free_fork(ph);
		ft_print_mes(ph, "%lu: %d is sleeping\n");
		ft_usleep(ph->all->t_sleep, ph->all);
		ft_print_mes(ph, "%lu: %d is thinking\n");
	}
}

void	ft_control_death(t_data *data, int i, int feed)
{
	while (1)
	{
		i = -1;
		feed = 0;
		while (++i < data->count_ph)
		{
			if ((int)(ft_get_time(data) - data->ph[i].t_last_eat)
					> data->t_die)
			{
				ft_output("%lu: %d died\n", data, i);
				return ;
			}
			if (data->eat_end != -1 && data->ph[i].eat_count >= data->eat_end)
				feed++;
		}
		if (feed == data->count_ph)
		{
			ft_output("%lu: all philosofers eated %d times\n",
				data, data->eat_end - 1);
			return ;
		}
		usleep(50);
	}
}

int	ft_clear_data(t_data *data)
{
	free (data->forks);
	free (data->ph);
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_data	data;

	if (argc < 5 || argc > 6 || !ft_init_input(argc, argv, &data))
	{
		write(1, "wrong inputs\n", 13);
		return (1);
	}
	data.st_time = ft_get_time(&data);
	i = -1;
	while (++i < data.count_ph)
	{
		if (pthread_create(&data.ph[i].t, NULL,
				ft_philo_live, &data.ph[i]) != 0)
			return (ft_clear_data(&data));
	}
	ft_control_death(&data, 0, 0);
	usleep(100);
	ft_clear_data(&data);
	i = -1;
	while (++i < data.count_ph)
		pthread_detach(data.ph[i].t);
	return (0);
}
