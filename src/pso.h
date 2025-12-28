#ifndef PSO_H
#define PSO_H

#include "map.h"

typedef struct
{
    double x;
    double y;
    double vx;
    double vy;

    double pBest_x;
    double pBest_y;
    double pBest_value;
} Particle;

typedef struct
{
    Particle *particles;
    int particle_count;

    double gBest_x;
    double gBest_y;
    double gBest_value;

    double w;
    double c1;
    double c2;
    double r1;
    double r2;
} Swarm;

Swarm* init_swarm(int particle_count, Map *map, double w, double c1, double c2, double r1, double r2);

void update_swarm(Swarm *swarm, Map *map);

void free_swarm(Swarm *swarm);

#endif