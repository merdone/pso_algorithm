#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "generator_utils.h"

int main(int argc, char *argv[])
{
    if (argc < 6)
    {
        printf("Usage: %s <width> <height> <max_signal> <radius> <filename>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    double max_signal = atoi(argv[3]);
    double radius = atoi(argv[4]);
    char *filename = argv[5];
    generate_map(filename, width, height, max_signal, radius);
    return 0;
}