#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data	t_data;

typedef struct s_ph
{
	int				id;
	pid_t			pid;
	pthread_t		t;
	struct timeval	t_last_eat;
	int				eat_count;
	t_data			*all;
	sem_t			*eat_c_monitor;
}	t_ph;

typedef struct s_data
{
	struct timeval	st_time;
	int				count_ph;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				eat_end;
	t_ph			*ph;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*the_end;
	sem_t			*died;
}	t_data;

int				ft_init_input(int argc, char **argv, t_data *data);

void			ft_take_fork(t_ph *ph);
void			ft_free_fork(t_ph *ph);
void			ft_output(char *s, t_data *data, int i);
int				ft_usleep(unsigned long msec, t_data *data);

int				ft_atoi(char *num);
int				ft_strlen(char *s);
int				ft_is_digit(char c);
unsigned long	ft_get_time(t_data *data);
int				ft_get_dif_eat(t_ph *ph);
void			ft_print_mes(t_ph *ph, char *s);

void			*ft_control_death(void *philos);
void			*ft_control_count(void *d);
void			ft_sems_unlinks(void);

#endif