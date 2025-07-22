#include "../inc/philo.h"

static int  inits(t_simulation *sim, int argc, char **argv)
{
    if (parse(sim, argc, argv) == FAILURE)
        return (FAILURE);
    if (init_sim(sim) == FAILURE)
        return (FAILURE);
    return (SUCCESS);
}

static int  run_sim(t_sim *sim)
{

}

int main(int argc, char **argv)
{
    t_sim   sim;

    if (inits(&sim, argc, argv) == FAILURE)
        return (FAILURE) ;
    if (run_sim(&sim) == FAILURE)
    {
        free_sim(&sim);
        return (FAILURE);
    }
    free_sim(&sim);
    return (SUCCESS);
}