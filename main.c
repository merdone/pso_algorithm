#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "map.h"
#include "pso.h"
#include "logger.h"
#include "utils.h"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_usage(argv[0]);
        return 1;
    }

    srand(time(NULL));

    char *map_filename = argv[1];

    int particle_count = 30;
    int iterations = 100;
    int log_interval = 0;

    double w = 0.5;
    double c1 = 1.0;
    double c2 = 1.0;
    double r1 = -1.0;
    double r2 = -1.0;

    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "-p") == 0 && i + 1 < argc)
        {
            particle_count = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc)
        {
            iterations = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc)
        {
            log_interval = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc)
        {
            char *config_file = argv[++i];
            if (read_config(config_file, &w, &c1, &r1, &c2, &r2) == -1)
            {
                return 1;
            }
        }
    }

    printf("Start symulacji: \nMapa=%s, \nCzastki=%d, \nIteracje=%d\n", map_filename, particle_count, iterations);

    Map *map = init_map(map_filename);
    if (map == NULL)
    {
        fprintf(stderr, "Blad: Nie udalo sie wczytac mapy.\n");
        return 2;
    }

    Swarm *swarm = init_swarm(particle_count, map, w, c1, c2, r1, r2);
    if (swarm == NULL)
    {
        fprintf(stderr, "Blad: Nie udalo sie utworzyc roju.\n");
        free_map(map);
        return 3;
    }

    char *log_filename = "results.csv";

    if (log_interval > 0)
    {
        init_logger(log_filename);
        save_iteration(log_filename, 0, swarm);
    }

    for (int t = 1; t <= iterations; t++)
    {
        update_swarm(swarm, map);
        if (log_interval > 0 && (t % log_interval == 0))
        {
            save_iteration(log_filename, t, swarm);
        }
    }

    print_result(swarm);

    free_swarm(swarm);
    free_map(map);

    return 0;
}