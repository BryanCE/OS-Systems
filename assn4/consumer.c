#include"consumer.h"
//takes a pointer to the outbuffer
void *consumer(void *pc)
{
	//because the pointer is void we need to assign
	//a prodcons pointer to this address
	//to access it's members
	struct prodcons *outbuffer = pc;//(struct prodcons*)pc;
	int number = 0;
	
	//again I tried lots of different while loops 
	//and loops to wait when the buffer was empty
	//but coudn't seem to get the logic right 
	//without entering infinite loops
	for(int i = 0; i < outbuffer->argc - 1; i++)
	{
		//first number in the outbuffer should be
		//the original number that was factored
		//so pop it off to print separetly
		//getting the output formatted was a pain
		//this took me forever for some reason:w
		number = pc_pop(outbuffer);
		//printf("\n%d: ", number);
		//check that 0 wasn't passed in
		if(number <= 0)
		{
			printf("\nNumber to factor can't be 0!\n");
			break;
		}
		//this prints just the original number before we
		//loop through the rest
		printf("%d: ", number);

		//now we can loop through the rest of outbuffer
		//checking for 0's which separate the groups
		//of prime factors
		//so the first number has already been popped off
		while(number != 0)
		{
			//if the number isn't 0 pop off the next in line
			//this could now be a zero if the first one 
			//was < 4
			//so check it again to see if we need to print it
			number = pc_pop(outbuffer);	
			if(number != 0)
			{
				printf("%d, ", number);
			}
		}
		printf("\n");
	}
	//all printing is done so exit
	pthread_exit(0);
}//end consumer

