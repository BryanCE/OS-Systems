#include"producer.h"
//#include"prodcons.h"

//factor2pc factors numbers and sends them
//out to the consumer function
//it returns an array of the factored numbers 
//i don't know how JP did it without this

int *factor2pc(int num)
{
	//index variable
	int index = 0;
	//start by dividing by 2 then increment when needed
	int divisor = 2;
	//gets returned to consumer to place in outbuffer
	static int factors[MAX_FACTORS];
	//loop through trying to factor
	//if it doesn't increment the divisor
	while(num > 1)
		//if divides by 2 evenly then add
		//what you divided it by into the factors array
		if(num % divisor == 0)
		{
			//add to the factors array
			factors[index++] = divisor;
			//num is divided evenly here so update
			//what needs to be the new numerator
			num /= divisor;
		}
		else
		{
			//this means the numerator hasn't
			//divied evenly using current divisor
			//so increment divisor and try again
			divisor += 1;
		}
	//num has been divided down to 2
	//it can no longer be divided any smaller
	//so return the array which holds all the divisors
	return factors;
}



//producer function takes in a prodcons buffer
void *producer(void *pc)
{
	//producer creates a consumer
	pthread_t consumer_ID;
	//keeps track of incoming number
	int tobefactored = 0;

	//pointer to the incoming prodcon structure
	struct prodcons *inbuffer = pc;

	//make and initialize the outbuffer
	//shared with consumer
	struct prodcons *outbuffer = malloc(sizeof(struct prodcons));
	pc_init(outbuffer, inbuffer->argc);
	//make a consumer thread and check if there was
	//an issue creating it. 
	int consumer_RC = pthread_create(&consumer_ID, NULL, consumer, outbuffer);
	if(consumer_RC != 0)
	{
		fprintf(stderr, "Could no create Consumer thread!\n");
		pthread_exit(NULL);
	}
	
	//i sent the argc count to each buffer to track each
	//original number
	//so if we have more original args keep going
	//i tried using a while loop and could't ever
	//seem to get the right conditions without just using 
	//a for loop and adding an arg count
	//i tried to do busy waiting in a million different ways 
	//with while loops checking and I kept getting
	//into infinite loops and the progrtam would end
	//i'd get stuc in a thread that would never close
	//and it was much more complicated. 
	for(int i = 0; i < inbuffer->argc -1; i++)
	{
		//pop off a number
		tobefactored = pc_pop(inbuffer);
		//add it to consumer thread
		pc_push(outbuffer, tobefactored);
		//do prime factorization
		//which returns an array with the factors in it
		//I was sure how else to keep them grouped
		int *factors = factor2pc(tobefactored);
		
		

		//put prime factors into the outbuffer
		for(int j = 0; j < MAX_FACTORS; j++)
		{
			//adding a 0 to separate grouped factors in the
			//outbuffer
			if(factors[j] <= 0)
			{
				pc_push(outbuffer, 0);
				break;
			}
			//factors contains a number > 0
			//so push it onto the outbuffer
			pc_push(outbuffer, factors[j]);
		}

		//another thread will need this so empty it out
		for(int k = 0; k < MAX_FACTORS; k++)
		{
			factors[k] = 0;
		}
	}
	pthread_join(consumer_ID, NULL);
	pthread_exit(0);
}//end producer




















