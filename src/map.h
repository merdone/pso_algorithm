#ifndef MAP_H
#define MAP_H

typedef struct
{
    int width;
    int height;
    double **values;
} Map;

int read_size(FILE *in, int *width, int *height);

double **read_values(FILE *in, int width, int height);

Map* init_map(char *filename);

void free_map(Map *map);

#endif