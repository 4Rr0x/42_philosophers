/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:06:16 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/05 15:02:34 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static void	assign_forks(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
		{
			printf("Error: mutex init\n");
			destroy_forks_on_failure(sim->forks, i);
			return ;
		}
		i++;
	}
}

static int	init_forks(t_sim *sim)
{
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->num_philos);
	if (!sim->forks)
	{
		printf("Error: malloc forks\n");
		return (FAILURE);
	}
	assign_forks(sim);
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
	{
		printf("Error: mutex init\n");
		destroy_forks_on_failure(sim->forks, sim->num_philos);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	create_philos(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		sim->philos[i].id = i + 1;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].last_meal = sim->start_timestamp;
		sim->philos[i].sim = sim;
		if (pthread_mutex_init(&sim->philos[i].meal_mutex, NULL) != 0)
		{
			printf("Error: mutex init\n");
			destroy_philos_on_failure(sim->philos, i);
			return ;
		}
		i++;
	}
}

static int	init_philos(t_sim *sim)
{
	sim->philos = malloc(sizeof(t_philo) * sim->num_philos);
	if (!sim->philos)
	{
		printf("Error: malloc philos\n");
		return (FAILURE);
	}
	create_philos(sim);
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
	{
		printf("Error: mutex init (print_mutex)\n");
		destroy_forks_on_failure(sim->forks, sim->num_philos);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	init_sim(t_sim *sim)
{
	sim->sim_finished = 0;
	sim->start_timestamp = current_timestamp_ms();
	if (init_forks(sim) == FAILURE)
		return (FAILURE);
	if (pthread_mutex_init(&sim->eating_lock, NULL) != 0)
	{
		printf("Error: mutex init (eating_lock)\n");
		destroy_forks_on_failure(sim->forks, sim->num_philos);
		return (FAILURE);
	}
	if (pthread_mutex_init(&sim->finish_mutex, NULL) != 0)
	{
		printf("Error: mutex init (finish_mutex)\n");
		pthread_mutex_destroy(&sim->eating_lock);
		destroy_forks_on_failure(sim->forks, sim->num_philos);
		return (FAILURE);
	}
	if (init_philos(sim) == FAILURE)
	{
		pthread_mutex_destroy(&sim->finish_mutex);
		pthread_mutex_destroy(&sim->eating_lock);
		destroy_forks_on_failure(sim->forks, sim->num_philos);
		return (FAILURE);
	}
	return (SUCCESS);
}
