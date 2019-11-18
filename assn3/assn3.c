#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
 Promise of Originality
 I promise that this source code file has, in it's entirety, been
 written by myself and by no other person or persons. If at any time an
 exact copy of this source code is found to be used by another person in
 this term, I understand that both myself and the student that submitted
 the copy will receive a zero on this assignment.
 */




void *runner(void *param); //threads call this function
//function pointer points to this (outside *runner)  
 


int main(int argc, char *argv[])
{

	int returnCode; //using this to check if pthread worked
	int *result; //a pointer to the prime fcators 
	//pFactors is what pthread_join uses to hold the prime factors
	//that were calculated in runner
	void *pFactors; //a flexible pointer to grab the array being passed back by the runner 
	pthread_t tid[argc-1]; //the thread identifier array to hold ID's
	pthread_attr_t attr; //set of thread attributes

	printf("\nAssignment: 3. Multiple Threads to calculate Prime Factors > 0.\n\n");

	//Old Code 
	//if(argc != 2) 
	//{
	//	fprintf(stderr, "usage: a.out <integer value>\n");
	//	return -1;
	//}
	

	//for testing purposes	
	/*for(int i = 1; i < argc; i++)
	{
		printf("%s, ", argv[i]);
	} */

	printf("\n");	

	//checking that integer passed in is > 0
	if(atoi(argv[1]) < 0)
	{
		fprintf(stderr, "%d must be >= 0\n" ,atoi(argv[1])); 
		return -1; 
	}

	//get the default attributes
	//initialize all threads with default values
	for(int i = 1; i < argc; i++)
	{
		pthread_attr_init(&attr);
	}

//separate pthread_attr_inti and pthread_create with two separate for loops
//if they are in one they run sequencially instead of parrallel to eachother. 
	//create thread
	//like fork()
	//&tid needs to be an array to handle 100 or more threads.
	//but also includes the exec thing by passing in third param runner to give it a job
	//use tid[i] and argv[i] in a for loop to handle individual threads.
	//creating and running each process through runner
	for(int i = 1; i < argc; i++)
	{	
		returnCode = pthread_create(&tid[i], &attr, runner, argv[i]);
		if(returnCode != 0)
		{
			printf("Failure to start thread. Returned: %d\n", returnCode);
			return -1;
		}
	}
	//to pass a function into pthread_create it has to be a pointer 
	//to a function. 

	//wait for the thread to exit
	//like the wait system call
	
	//joining each thread 
	for(int i = 1; i < argc; i++)
	{
		//joining threads
		//thread target = tid[i], the address of pFactors
		//is where the prime factors array is held
		//the terminating thread passes it back through pthread_exit()
		returnCode = pthread_join(tid[i], &pFactors);
		//result is an integer array that we can print but pFactors
		//holds the data so we have to make result point to pFactors
		//because pFactors is void it won't print using printf
		result = pFactors; 
		//if join doesn't work give error
		if(returnCode != 0)
		{
			printf("Failed to join thread!");
			return -1;
		}
		else
		{
			//print original number
			printf("%s: ", argv[i]);
			//end of pFactors and result is 0 so we can find the end
			//so keep looping until then to print
			while(*result != 0)
			{
				printf("%d, ", *result);
				result++;
			}
		}
		//free up memory used by pFactors
		free(pFactors); 
		printf("\n");
	}

	//notes from class
	//HINT when using wait something was passed to parent, 
	//instead of NULL use something else to 
	//pass back answer. 

	printf("\n\n"); 
	return 0;  

}//end main()



//left the name as runner but calculates prime factors of numbers 
//then passes back an array holding those values
//through pthread_exit
void *runner(void *number)
{
	int *primeFactors = malloc(sizeof(int));//dynamic array to hold numbers
	int num = atoi((char*)number); //get actual number value
	int index = 0;//index position used to move through primeFactors array 
	int size = 1; //separate number to keep track of size of the array
	int divisor = 2; //original divisor of 2 but increments later
	
	if(num < 4)
	{
		//double checking where we are and if we need more room
		//i had some strange errors and segmentation faults without this
		//i guess it was going out of bounds of the array
		if(index == size){
			//size++; 
			primeFactors = realloc(primeFactors, size*sizeof(int));
		}
		
		//if it's less than 4 its prime
		primeFactors[index] = num;
		index++;	
	}
	else
	{		
		while(num > 1)
		{
			//divide by 2 as many times as possible
			while(num % divisor == 0)
			{
				//if primefactors is too small to hold results make it bigger
				//increment size too
				if(index == size)
				{
					size++;
					primeFactors = realloc(primeFactors, size * sizeof(int));
				}
				//divide number by divisor(2) then assaign result to num
				//if this works store the divisor or prime factor in array
				//then move to the next spot in array
				num /= divisor;
				primeFactors[index] = divisor;
				index++; 	
			}
			//when num can no longer be divided by current divisor starting at 2
			//then increment divisor 
			divisor++;
		}
	}
	//check for enough space again
	//reallocate if needed. 
	if(index == size)
	{
		size++;
		primeFactors = realloc(primeFactors, size*sizeof(int));
	}
	primeFactors[index] = 0; 
	pthread_exit((void*)primeFactors);//passing back the array of factors
}//end runner()
