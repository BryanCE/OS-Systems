#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//max size of process Q plus space to allow 
//shuffling of processes for the round robin algorithm.
#define PROCESS_MAX (102)
#define QUANTUM (100)

//a struct to more easily handle these processes and 
//their data from the file
struct process{
	int arrvltime, brsttime, rspnstime, waittime, TAtime, rmngtime, timedone, runstart, runend;
	bool running, done, interupt, active, ImNew;
};

//a globally available readyQ for each algorithm to use
struct process readyQ[PROCESS_MAX]; 
//struct process tmp[PROCESS_MAX];
//used in Round Robin
//struct process arrvlQ[PROCESS_MAX];

//remove blanks from readyQ
void removeBlanks(struct process q[], int count);

//a function to reset the readyQ between algorithms
void reset(struct process *q, int count);

//reset a particular process
void resetProcess(struct process *q, int index);

//a function for printing
void print(char *alg, int count);

//declarations for the CPU scheduling algorithms
//First come first serve
void FCFS(int *arrvl, int *brst, int count);

//shortest job first version 2
void SJF2(int *arrvl, int *brst, int count);

//Shortest time remaining first
void SRTF(int *arrvl, int *brst, int count);

//Round Robin
void RR3(int * arrvl, int *brst, int count);

