#include "../includes/philo.h"

int	ft_live(t_ph *ph)
{
	gettimeofday(&ph->t_last_eat, NULL);
	pthread_create(&ph->t, NULL, ft_control_death, (void *)ph);
	if (ph->t == 0)
		return (1);
	pthread_detach(ph->t);
	while (1)
	{
		ft_take_fork(ph);
		gettimeofday(&ph->t_last_eat, NULL);
		ft_print_mes(ph, "%lu: %d is eating\n");
		ph->eat_count++;
		if (ph->eat_count == ph->all->eat_end)
			sem_post(ph->eat_c_monitor);
		ft_usleep(ph->all->t_eat, ph->all);
		ft_free_fork(ph);
		ft_print_mes(ph, "%lu: %d is sleeping\n");
		ft_usleep(ph->all->t_sleep, ph->all);
		ft_print_mes(ph, "%lu: %d is thinking\n");
	}
	return (0);
}

int	ft_create_proc(t_data *data)
{
	int			i;
	pthread_t	t;

	i = -1;
	while (++i < data->count_ph)
	{
		data->ph[i].pid = fork();
		if (data->ph[i].pid < 0)
			return (1);
		else if (data->ph[i].pid == 0)
		{
			ft_live(&data->ph[i]);
			exit (0);
		}
		usleep(50);
	}
	if (data->eat_end > 0)
	{
		pthread_create(&t, NULL, ft_control_count, (void *)data);
		pthread_detach(t);
	}
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
	gettimeofday(&data.st_time, NULL);
	i = -1;
	if (ft_create_proc(&data))
	{
		free (data.ph);
		ft_sems_unlinks();
		return (0);
	}
	i = -1;
	sem_wait(data.died);
	ft_sems_unlinks();
	while (++i < data.count_ph)
		kill(data.ph[i].pid, SIGKILL);
	free (data.ph);
	return (0);
}
