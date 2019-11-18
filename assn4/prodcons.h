#ifndef PRODCONS_H
#define PRODCONS_H
//buffer size
#define BUFFER_SIZE 50

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>


struct prodcons {
	int buffer[BUFFER_SIZE];
	int inposition;
	int outposition;
	int argc;

	//i couldn't get things to work right 
	//without the conditiom variables
	//it took days to figure out
	pthread_cond_t full;
	pthread_cond_t empty;
	pthread_mutex_t lock;
};


void pc_init(struct prodcons *pc, int argc);
int pc_pop(struct prodcons *pc);
void pc_push(struct prodcons *pc, int val);

#endif
