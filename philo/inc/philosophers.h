/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:58:27 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/05 15:02:10 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>

/* ************************************************************************** */
/*                                                                            */
/*                                  Settings                                  */
/*                                                                            */
/* ************************************************************************** */

# define DEBUG_MODE 0

/* ************************************************************************** */
/*                                                                            */
/*                           Argument Descriptions                            */
/*                                                                            */
/* ************************************************************************** */

# define ARG_NUM_PHILOSOPHERS "num_philos"
# define ARG_TIME_TO_DIE      "time_to_die"
# define ARG_TIME_TO_EAT      "time_to_eat"
# define ARG_TIME_TO_SLEEP    "time_to_sleep"
# define ARG_NUM_MUST_EAT     "num_must_eat"

/* ************************************************************************** */
/*                                                                            */
/*                            Structs Declaration                             */
/*                                                                            */
/* ************************************************************************** */

struct	s_sim;

typedef struct s_philo
{
	int					id;
	int					meals_eaten;

	long				last_meal;

	pthread_t			thread;
	pthread_mutex_t		meal_mutex;

	struct s_sim	*sim;
}	t_philo;

typedef struct s_sim
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_must_eat;
	int				sim_finished;

	long			start_timestamp;

	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	eating_lock;
	pthread_mutex_t	finish_mutex;

	t_philo	*philos;
}	t_sim;

typedef enum e_status
{
	ERROR	= -1,
	SUCCESS = 0,
	FAILURE = 1
}	t_status;

/* ************************************************************************** */
/*                                                                            */
/*                               Initialization                               */
/*                                                                            */
/* ************************************************************************** */

int			init_sim(t_sim *sim);
int			is_sim_finished(t_sim *sim);
void		set_sim_finished(t_sim *sim, int status);

/* ************************************************************************** */
/*                                                                            */
/*                                  Parsing                                   */
/*                                                                            */
/* ************************************************************************** */

int			parse_args(t_sim *sim, int argc, char **argv);

/* ************************************************************************** */
/*                                                                            */
/*                             Thread Management                              */
/*                                                                            */
/* ************************************************************************** */

int			create_philo_threads(t_sim *sim);
void		join_philo_threads(t_sim *sim);

/* ************************************************************************** */
/*                                                                            */
/*                             Philosopher Logic                              */
/*                                                                            */
/* ************************************************************************** */

void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);

/* ************************************************************************** */
/*                                                                            */
/*                                   Utils                                    */
/*                                                                            */
/* ************************************************************************** */

int			is_positive_integer(const char *str);
const char	*get_arg_description(int index);
long		current_timestamp_ms(void);
void		precise_sleep(t_sim *sim, int duration_ms);

/* ************************************************************************** */
/*                                                                            */
/*                              Debug & Messages                              */
/*                                                                            */
/* ************************************************************************** */

void		print_state(t_philo *philo, const char *msg);
void		debug_print(const char *msg);
void		debug_sim(t_sim *sim);

/* ************************************************************************** */
/*                                                                            */
/*                                  Cleanup                                   */
/*                                                                            */
/* ************************************************************************** */

void		destroy_sim(t_sim *sim);
void		destroy_forks_on_failure(pthread_mutex_t *forks, int count);
void		destroy_philos_on_failure(t_philo *philos,
				int count);

#endif
