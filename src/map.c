#include <stdio.h>
#include <stdlib.h>

#include "map.h"

int read_size(FILE *in, int *width, int *height)
{
    if (fscanf(in, "%d %d", width, height) != 2)
    {
        return -1;
    }

    return 0;
}

double **read_values(FILE *in, int width, int height)
{
    double **values = malloc(sizeof(double *) * height);
    for (int i = 0; i < height; i++)
    {
        values[i] = malloc(sizeof(double) * width);
    }
    double temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fscanf(in, "%lf", &temp);
            values[i][j] = temp;
        }
    }
    return values;
}

Map* init_map(char *filename)
{
    Map *map = malloc(sizeof(Map));

    FILE *in = fopen(filename, "r");
    if (in == NULL)
    {
        return NULL;
    }

    int height, width;

    if (read_size(in, &width, &height) != 0)
    {
        free(map);
        return NULL;
    }
    double **values = read_values(in, width, height);

    if (values == NULL)
    {
        free(map);
        fclose(in);
        return NULL;
    }

    (*map).height = height;
    map->width = width;
    map->values = values;

    fclose(in);
    return map;
}

void free_map(Map *map)
{
    for (int i = 0; i < map->height; i++)
    {
        free(map->values[i]);
    }
    free(map->values);
}