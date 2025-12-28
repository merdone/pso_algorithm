#ifndef UTILS_H
#define UTILS_H

#include "pso.h"

double random_0_1();

double random_range(double min, double max);

void print_usage(char *prog_name);

void print_result(Swarm *swarm);

int read_config(char *config_file, double *w, double *c1, double *c2, double *r1, double *r2);

double distance(int x1, int y1, int x2, int y2);

#endif