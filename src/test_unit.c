#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "map.h"
#include "pso.h"
#include "generator_utils.h"

void test_map_loading()
{
    char *filename = "test_unit_map.tmp";

    generate_map(filename, 10, 5, 7.5, 5);

    Map *map = init_map(filename);

    assert(map != NULL);
    assert(map->width == 10);
    assert(map->height == 5);
    assert(map->values[0][0] <= 7.5);
    assert(map->values[4][9] <= 7.5);

    free_map(map);
    remove(filename);
    printf("Passed map loading test! \n");
}

void test_swarm_init()
{
    Map map;
    map.width = 100;
    map.height = 100;
    map.values = malloc(sizeof(double *) * map.height);

    for (int i = 0; i < map.height; i++)
    {
        map.values[i] = malloc(sizeof(double) * map.width);
        for (int j = 0; j < map.width; j++)
        {
            map.values[i][j] = 0.0;
        }
    }

    int particles_count = 50;

    Swarm *swarm = init_swarm(particles_count, &map, 0.5, 1.0, 1.0, -1, -1);

    assert(swarm != NULL);
    assert(swarm->particle_count == 50);
    assert(swarm->w == 0.5);

    for (int i = 0; i < particles_count; i++)
    {
        double x = swarm->particles[i].x;
        double y = swarm->particles[i].y;

        assert(x >= 0 && x <= 100);
        assert(y >= 0 && y <= 100);

        assert(swarm->particles[i].vx == 0);
        assert(swarm->particles[i].vy == 0);
    }

    free_swarm(swarm);
    free_map(&map);
    printf("Passed swarm init test! \n");
}

int main()
{
    printf("=== Unit tests were started ===\n\n");

    test_map_loading();
    test_swarm_init();

    printf("\n=== All tests were finished ===\n");
    return 0;
}