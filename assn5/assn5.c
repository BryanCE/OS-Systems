/*
   Bryan Edman
   CS3060-001 Fall 2019
   Assignment 5

   Promise of Originality
   I promise that this source code file has, in it's entirety, been
   written by myself and by no other person or persons. If at any time an
   exact copy of this source code is found to be used by another person in
   this term, I understand that both myself and the student that submitted
   the copy will receive a zero on this assignment.
*/




#include<stdio.h>
#include<stdlib.h>

//include the scheduling algorithms
#include"schedulingAlgs.h"


int main(int argc, char *argv[]){

	printf("\nAssignment 5: CPU Scheduling.\nBryan Edman\nCS3060\n\n");
	if(argc == 1 || argc > 2)
	{
		printf("\nMUST PROVIDE A VALID FILE NAME\nPlease run again and provide a file as an argument in the form ./assn5 example.txt\nI didn't notice JP used a < to read the file in.\nPlease just use a space in between program name and file name.\n\n");
		return -1;
	}


	//first things first make arrays to hold data from
	//the processes like burst time and when they came in
	int bursttime[100];
	int arrivaltime[100];

	//open the file of data
	FILE *datafile;
	if(argc > 1)
	{
		datafile = fopen(argv[1], "r");
		if(datafile == NULL)
		{
			perror("ERROR OPENING FILE!");
			return -1;
		}
	}


	//while loop for gathering bursttime data
	//variables for while
	int i = 0;
	int number;
	while(fscanf(datafile, "%d", &number) != EOF)
	{
		//add first number
		arrivaltime[i] = number;
		//get second number
		fscanf(datafile, "%d", &number);
		bursttime[i] = number;
		i++;
	}
	//keeping track of the number of processes
	int count = i;
	//closing the file
	fclose(datafile);

	if(count > 101)
	{
		fprintf(stderr, "\nThis program only handles up to 100 processes!\n");
	}

//	//test print of incoming data to check for 
//	//correct formatting
//	for(int i = 0; i < processCount; i++)
//	{
//		printf("Arrival: %d, Burst: %d\n",arrivaltime[i], bursttime[i]);
//	}

	//start sending the data to the different algorithms. 
	//FCFS first
	FCFS(arrivaltime, bursttime, count);

	//Shortest job first
	SJF2(arrivaltime, bursttime, count);

	//shortest remaining time first
	SRTF(arrivaltime, bursttime, count);

	//round robin
	RR3(arrivaltime, bursttime, count);	


	return 0;
}
