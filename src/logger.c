#include <stdio.h>
#include <stdlib.h>

#include "logger.h"

void init_logger(char *filename)
{
    FILE *f = fopen(filename, "w");
    if (f == NULL)
    {
        fprintf(stderr, "Blad: Nie mozna stworzyc pliku logu %s\n", filename);
        return;
    }

    fprintf(f, "iteration,particle_id,x,y,fitness\n");
    fclose(f);
}

void save_iteration(char *filename, int iteration, Swarm *swarm)
{
    FILE *f = fopen(filename, "a");
    if (f == NULL)
    {
        fprintf(stderr, "Blad: Nie mozna otworzyc pliku logu do zapisu\n");
        return;
    }

    for (int i = 0; i < swarm->particle_count; i++)
    {
        Particle p = swarm->particles[i];
        fprintf(f, "%d,%d,%.4f,%.4f,%.4f\n", iteration, i, p.x, p.y, p.pBest_value);
    }

    fclose(f);
}