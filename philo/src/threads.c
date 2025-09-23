/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paalexan <paalexan@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:47:44 by paalexan          #+#    #+#             */
/*   Updated: 2025/08/05 13:37:58 by paalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	create_philo_threads(t_sim *sim)
{
	int	i;
	int	j;

	i = 0;
	while (i < sim->num_philos)
	{
		if (pthread_create(&sim->philos[i].thread, NULL,
				philo_routine, &sim->philos[i]) != 0)
		{
			printf("Error: failed to create thread for philo %i\n",
				i + 1);
			pthread_mutex_lock(&sim->finish_mutex);
			sim->sim_finished = 1;
			pthread_mutex_unlock(&sim->finish_mutex);
			j = 0;
			while (j < i)
			{
				pthread_join(sim->philos[j].thread, NULL);
				j++;
			}
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

// Joins all philo threads
void	join_philo_threads(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philos)
	{
		pthread_join(sim->philos[i].thread, NULL);
		i++;
	}
}
