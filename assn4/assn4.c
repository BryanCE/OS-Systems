//Bryan Edman
//CS3060
//Assignment: 4

//Promise of originality
//I promise that this source code file has,
//in its entirety, been written by myself
//and by no other person or persons. If at
//any time an exact copy of this source code
//is found to be used by another person in
//this term, I understand that both myself
//and the student that submitted the copy      
//will receive a zero on this assignment.

#include"prodcons.h"
#include"producer.h"
#include"consumer.h"

int main(int argc, char *argv[])
{
	printf("\nBryan Edman\nCS3060\nAssignment: 4\nSynchronization\n");
	
	//producer thread ID
	pthread_t producer_ID;

	//check if an argument is  0
	if(argc <= 1)
	{
		fprintf(stderr, "Must pass integer arguments > 0\n");
		return EXIT_FAILURE;
	}

	// make a buffer to share with producer
	struct prodcons *inbuffer = malloc(sizeof(struct prodcons));
	pc_init(inbuffer, argc);//also pass argc to keep track of original #s

	int producer_RC = pthread_create(&producer_ID, NULL, producer, inbuffer);
	if(producer_RC != 0)
	{
		fprintf(stderr, "Could not create producer thread!\n");
		return EXIT_FAILURE;
	}


	//insert numbers into inbuffer
	//as long as ther are more arguments
	for(int i = 1; i < argc; i++)
	{
		pc_push(inbuffer, atoi(argv[i]));
	}

	//join producer thread
	pthread_join(producer_ID, NULL);

	
	return 0;
}//end main
