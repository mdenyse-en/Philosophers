#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_ph
{
	int				id;
	pthread_t		t;
	unsigned long	t_last_eat;
	int				eat_count;
	t_data			*all;
}	t_ph;

typedef struct s_data
{
	unsigned long	st_time;
	int				count_ph;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_end;
	t_ph			*ph;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	the_end;
}	t_data;

int				ft_init_input(int argc, char **argv, t_data *data);

void			ft_take_fork(t_ph *ph);
void			ft_free_fork(t_ph *ph);
void			ft_output(char *s, t_data *data, int i);

int				ft_atoi(char *num);
int				ft_strlen(char *s);
int				ft_is_digit(char c);
unsigned long	ft_get_time(t_data *data);
void			ft_print_mes(t_ph *ph, char *s);

#endif