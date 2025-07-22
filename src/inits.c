#include "../inc/philosophers.h"

int init_sim(t_sim *sim)
{
    sim->finish = 0;
    sim->start_tmstp = get_timestamp();
    if (init_forks(sim) == FAILURE)
        return (FAILURE);
    if (mutex_init(&sim->eating_lock, NULL) != 0)
    {
        destroy_forks(sim->forks, sim->num_philos)
        return (FAILURE);
    }
    if (init_philos(sim) == FAILURE)
    {
        destroy_forks(sim->forks, sim->num_philos);
        return (FAILURE);
    }
    return (SUCCESS);
}