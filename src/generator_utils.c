#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void generate_map(char *filename, int width, int height, double max_signal, double radius)
{
    FILE *out = fopen(filename, "w");
    if (out == NULL)
    {
        return;
    }
    max_signal = max_signal - 1;
    int target_x = rand() % width;
    int target_y = rand() % height;

    fprintf(out, "%d %d\n", width, height);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double dist = distance(x, y, target_x, target_y);
            double value;
            if (dist < radius)
            {
                double noise = random_0_1() * 0.5;
                value = max_signal - dist + noise;
                if (x == target_x && y == target_y)
                {
                    value = max_signal + 1.0;
                }
            }
            else
            {
                value = -1000.0;
            }
            fprintf(out, "%.2f ", value);
        }
        fprintf(out, "\n");
    }
    fclose(out);
}

void create_test_map(const char *filename, int width, int height, int target_x, int target_y)
{
    FILE *out = fopen(filename, "w");
    if (out == NULL)
    {
        return;
    }

    fprintf(out, "%d %d\n", width, height);

    double max_signal = 1000.0;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            double d = distance(x, y, target_x, target_y);
            double value = max_signal - d;
            if (value < -1000)
            {
                value = -1000;
            }
            fprintf(out, "%.2f ", value);
        }
        fprintf(out, "\n");
    }
    fclose(out);
}