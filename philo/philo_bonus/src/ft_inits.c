#include "../includes/philo.h"

int	ft_check_input(int argc, char **argv)
{
	int	i;

	while (--argc > 0)
	{
		i = 0;
		while (argv[argc][i] != '\0')
		{
			if (!ft_is_digit(argv[argc][i++]))
				return (0);
		}
	}
	if (ft_atoi(argv[1]) <= 0)
		return (0);
	return (1);
}

t_ph	ft_init_ph(t_data *data, int i)
{
	t_ph	ph;

	ph.id = i + 1;
	ph.eat_count = 0;
	ph.all = data;
	sem_unlink("eat_monitor");
	ph.eat_c_monitor = sem_open("eat_monitor", O_CREAT, 0666, 0);
	if (ph.eat_c_monitor == SEM_FAILED)
		exit (0);
	return (ph);
}

int	ft_inits_semafors(t_data *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("the_end");
	sem_unlink("died");
	data->print = sem_open("print", O_CREAT | O_EXCL, 0666, 1);
	data->the_end = sem_open("the_end", O_CREAT | O_EXCL, 0666, 1);
	data->forks = sem_open("forks", O_CREAT, 0666, data->count_ph);
	data->died = sem_open("died", O_CREAT, 0666, 0);
	return (data->print != SEM_FAILED && data->the_end != SEM_FAILED
		&& data->forks != SEM_FAILED && data->died != SEM_FAILED);
}

int	ft_init_input(int argc, char **argv, t_data *data)
{
	int	i;

	if (!ft_check_input(argc, argv))
		return (0);
	data->count_ph = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	data->eat_end = -1;
	if (argc == 6)
		data->eat_end = ft_atoi(argv[5]);
	if (!ft_inits_semafors(data))
		return (0);
	data->ph = (t_ph *)malloc(data->count_ph * sizeof(t_ph));
	if (!data->ph)
		return (0);
	i = -1;
	while (++i < data->count_ph)
	{
		data->ph[i] = ft_init_ph(data, i);
		if (data->ph[i].eat_c_monitor == SEM_FAILED)
			return (0);
	}
	return (1);
}
