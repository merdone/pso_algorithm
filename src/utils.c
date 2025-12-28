#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "pso.h"

double random_0_1()
{
    return (double)rand() / RAND_MAX;
}

double random_range(double min, double max)
{
    return min + random_0_1() * (max - min);
}

void print_usage(char *prog_name)
{
    printf("Uzycie: %s <plik_mapy> [opcje]\n", prog_name);
    printf("Opcje:\n");
    printf("  -p <int>    Liczba czastek (domyslnie 30)\n");
    printf("  -i <int>    Liczba iteracji (domyslnie 100)\n");
    printf("  -c <plik>   Plik konfiguracyjny (w, c1, r1, c2, r2)\n");
    printf("  -n <int>    Interwal zapisu do logu (0 = brak zapisu)\n");
}

void print_result(Swarm *swarm)
{
    printf("\n--- Wyniki ---\n");
    printf("Znalezione optimum (gBest):\n");
    printf("X: %.4f\n", swarm->gBest_x);
    printf("Y: %.4f\n", swarm->gBest_y);
    printf("Wartosc sygnalu: %.4f\n", swarm->gBest_value);
}

double distance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int read_config(char *config_file, double *w, double *c1, double *c2, double *r1, double *r2)
{
    FILE *fc = fopen(config_file, "r");

    if (fc == NULL)
    {
        printf("Ostrzezenie: Nie mozna otworzyc pliku config %s. Uzywam domyslnych.\n", config_file);
        return -1;
    }

    int count = fscanf(fc, "%lf %lf %lf %lf %lf", w, c1, r1, c2, r2);

    if (count == -1)
    {
        count = 0;
    }
    
    fclose(fc);

    printf("Zaladowano konfiguracje:\n");
    printf("w = %.2f\n", *w);
    printf("c1 = %.2f\n", *c1);

    if (count >= 3)
    {
        printf("r1 = %.2f\n", *r1);
    }
    else
    {
        printf("r1 = random\n");
    }

    printf("c2 = %.2f\n", *c2);

    if (count == 5)
    {
        printf("r2 = %.2f\n", *r2);
    }
    else
    {
        printf("r2 = random\n");
    }

    printf("------------------------\n");

    return count;
}