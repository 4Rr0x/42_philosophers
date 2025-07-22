#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

typedef enum	e_status
{
	ERROR	= -1,
	SUCCESS = 0,
	FAILURE = 1
}	t_status;

typedef struct	s_sim
{
	int				num_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_must_eat;
	int				finish;

	long			start_tmstp;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eating_lock;

	t_philosopher	*philosophers;
}	t_sim;

typedef struct	s_philosopher
{
	int					id;
	int					meals_eaten;

	long				last_meal;

	pthread_t			thread;
	pthread_mutex_t		meal_mutex;

	struct s_simulation *sim;
}	t_philosopher;

#endif