#ifndef PRODUCER_H
#define PRODUCER_H


#include"prodcons.h"
#include"consumer.h"

#define MAX_FACTORS 20

int *factor2pc(int num);
void *producer(void *prodcons);
#endif
