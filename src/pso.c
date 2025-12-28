#include <stdlib.h>
#include <stdio.h>

#include "pso.h"
#include "utils.h"

static double get_fitness(Map *map, double x, double y)
{
    int int_x = (int)x;
    int int_y = (int)y;

    if (int_x < 0 || int_x >= map->width || int_y < 0 || int_y >= map->height)
    {
        return -1000000.0;
    }

    return map->values[int_y][int_x];
}

Swarm *init_swarm(int particle_count, Map *map, double w, double c1, double c2, double r1, double r2)
{
    Swarm *swarm = malloc(sizeof(Swarm));

    if (swarm == NULL)
    {
        return NULL;
    }

    swarm->particles = malloc(sizeof(Particle) * particle_count);

    if (swarm->particles == NULL)
    {
        free(swarm);
        return NULL;
    }

    swarm->particle_count = particle_count;
    swarm->w = w;
    swarm->c1 = c1;
    swarm->c2 = c2;
    swarm->r1 = r1;
    swarm->r2 = r2;

    swarm->gBest_value = -1000000.0;

    for (int i = 0; i < particle_count; i++)
    {
        swarm->particles[i].x = random_0_1() * map->width;
        swarm->particles[i].y = random_0_1() * map->height;

        swarm->particles[i].vx = 0;
        swarm->particles[i].vy = 0;

        swarm->particles[i].pBest_x = swarm->particles[i].x;
        swarm->particles[i].pBest_y = swarm->particles[i].y;

        double current_fitness = get_fitness(map, swarm->particles[i].x, swarm->particles[i].y);
        swarm->particles[i].pBest_value = current_fitness;

        if (current_fitness > swarm->gBest_value)
        {
            swarm->gBest_value = current_fitness;
            swarm->gBest_x = swarm->particles[i].x;
            swarm->gBest_y = swarm->particles[i].y;
        }
    }

    return swarm;
}

void update_swarm(Swarm *swarm, Map *map)
{
    for (int i = 0; i < swarm->particle_count; i++)
    {
        Particle *p = &swarm->particles[i];

        double r1, r2;
        if (swarm->r1 >= 0)
        {
            r1 = swarm->r1;
        }
        else
        {
            r1 = random_0_1();
        }

        if (swarm->r2 >= 0)
        {
            r2 = swarm->r2;
        }
        else
        {
            r2 = random_0_1();
        }

        p->vx = swarm->w * p->vx + swarm->c1 * r1 * (p->pBest_x - p->x) + swarm->c2 * r2 * (swarm->gBest_x - p->x);

        p->vy = swarm->w * p->vy + swarm->c1 * r1 * (p->pBest_y - p->y) + swarm->c2 * r2 * (swarm->gBest_y - p->y);

        p->x = p->x + p->vx;
        p->y = p->y + p->vy;

        double current_fitness = get_fitness(map, p->x, p->y);

        if (current_fitness > p->pBest_value)
        {
            p->pBest_value = current_fitness;
            p->pBest_x = p->x;
            p->pBest_y = p->y;

            if (current_fitness > swarm->gBest_value)
            {
                swarm->gBest_value = current_fitness;
                swarm->gBest_x = p->x;
                swarm->gBest_y = p->y;
            }
        }
    }
}

void free_swarm(Swarm *swarm)
{
    if (swarm != NULL)
    {
        free(swarm->particles);
        free(swarm);
    }
}