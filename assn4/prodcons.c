#include"prodcons.h"

void pc_init(struct prodcons *pc, int argc)
{
	pc->inposition = 0;
	pc->outposition = 0;
	pc->argc = argc;
	pthread_cond_init(&pc->full, 0);
	pthread_cond_init(&pc->empty, 0);
	pthread_mutex_init(&pc->lock, 0);

}

void pc_push(struct prodcons *pc, int val)
{
	//locking inside push and pop because 
	//the structure has it's own lock and key
	pthread_mutex_lock(&pc->lock);

	//if buffer is full wait
	while((pc->inposition +1) % BUFFER_SIZE == pc->outposition)
		pthread_cond_wait(&pc->empty, &pc->lock);

	//putting the values into the actual buffer
	pc->buffer[pc->inposition] = val;
	//this just rotates the buffer position if it reaches
	//the max size of the buffer
	pc->inposition = (pc->inposition + 1) % BUFFER_SIZE;
	
	//without this i was still getting race conditions
	//and undefined behavior. or deadlock
	pthread_cond_signal(&pc->full);

	//done adding things so release the lock
	pthread_mutex_unlock(&pc->lock);
}//end push



int pc_pop(struct prodcons *pc)
{
	//get lock on buffer
	pthread_mutex_lock(&pc->lock);

	//wait if buffer is empty
	while(pc->inposition == pc->outposition)
		pthread_cond_wait(&pc->full, &pc->lock);

	//remove the value
	int number = pc->buffer[pc->outposition];
	//update where in the buffer you are and circle back if needed
	pc->outposition = (pc->outposition + 1) % BUFFER_SIZE;


	//signal to anyone waiting 
	pthread_cond_signal(&pc->empty);
	//get rid of the lock
	pthread_mutex_unlock(&pc->lock);

	return number;
}//end pop
