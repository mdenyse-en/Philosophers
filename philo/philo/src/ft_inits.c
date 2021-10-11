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
	ph.t_last_eat = 0;
	ph.eat_count = 0;
	ph.all = data;
	return (ph);
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
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->the_end, NULL);
	data->ph = (t_ph *)malloc(data->count_ph * sizeof(t_ph));
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->count_ph);
	if (!data->ph || !data->forks)
		return (0);
	i = -1;
	while (++i < data->count_ph)
		data->ph[i] = ft_init_ph(data, i);
	i = -1;
	while (++i < data->count_ph)
		pthread_mutex_init(&data->forks[i], NULL);
	return (1);
}
