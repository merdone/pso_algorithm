#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "map.h"
#include "pso.h"
#include "utils.h"
#include "generator_utils.h"

int run_test_case(char *map_name, int w, int h, int target_x, int target_y)
{
    printf("Test: Map %dx%d, Target at (%d, %d)\n", w, h, target_x, target_y);

    create_test_map(map_name, w, h, target_x, target_y);

    Map *map = init_map(map_name);
    Swarm *swarm = init_swarm(50, map, 0.5, 1.0, 1.0, -1, -1);

    for (int i = 0; i < 100; i++)
    {
        update_swarm(swarm, map);
    }

    double diff_x = fabs(swarm->gBest_x - target_x);
    double diff_y = fabs(swarm->gBest_y - target_y);

    int passed = (diff_x <= 2.0 && diff_y <= 2.0);

    if (passed)
    {
        printf("Test passed! (Found: %.1f, %.1f)\n", swarm->gBest_x, swarm->gBest_y);
    }
    else
    {
        printf("Test failed! (Found: %.1f, %.1f, Expected: %d, %d)\n", swarm->gBest_x, swarm->gBest_y, target_x, target_y);
    }
    printf("\n");

    free_swarm(swarm);
    free_map(map);
    remove(map_name);
    return passed;
}

int main()
{
    printf("=== Running functional tests ===\n");

    int passed = 0;
    int total = 0;

    total++;
    if (run_test_case("test_map_1.txt", 50, 50, 25, 25))
        passed++;

    total++;
    if (run_test_case("test_map_2.txt", 30, 30, 2, 2))
        passed++;

    total++;
    if (run_test_case("test_map_3.txt", 20, 20, 18, 18))
        passed++;

    printf("=== Result: %d/%d tests passed ===\n", passed, total);

    return (passed == total) ? 0 : 1;
}