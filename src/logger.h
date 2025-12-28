#ifndef LOGGER_H
#define LOGGER_H

#include "pso.h"

void init_logger(char *filename);

void save_iteration(char *filename, int iteration, Swarm *swarm);

#endif