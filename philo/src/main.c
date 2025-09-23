/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 17:38:26 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/05 15:03:04 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	setup_sim(t_sim *sim, int argc, char **argv)
{
	if (parse_args(sim, argc, argv) == FAILURE)
		return (FAILURE);
	if (init_sim(sim) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int	run_sim(t_sim *sim)
{
	pthread_t	monitor_thread;

	if (create_philo_threads(sim) == FAILURE)
	{
		destroy_sim(sim);
		return (FAILURE);
	}
	if (pthread_create(&monitor_thread, NULL, monitor_routine, sim) != 0)
	{
		printf("Error: failed to create monitor thread\n");
		return (FAILURE);
	}
	pthread_join(monitor_thread, NULL);
	join_philo_threads(sim);
	return (SUCCESS);
}

int	is_sim_finished(t_sim *sim)
{
	int	finished;

	pthread_mutex_lock(&sim->finish_mutex);
	finished = sim->sim_finished;
	pthread_mutex_unlock(&sim->finish_mutex);
	return (finished);
}

void	set_sim_finished(t_sim *sim, int status)
{
	pthread_mutex_lock(&sim->finish_mutex);
	sim->sim_finished = status;
	pthread_mutex_unlock(&sim->finish_mutex);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (setup_sim(&sim, argc, argv) == FAILURE)
		return (FAILURE);
	if (run_sim(&sim) == FAILURE)
	{
		destroy_sim(&sim);
		return (FAILURE);
	}
	destroy_sim(&sim);
	return (SUCCESS);
}
