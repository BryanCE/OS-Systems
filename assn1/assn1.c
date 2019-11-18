//Bryan Edman
//CS3060-001 Fall 2019
//Assignment:1
//Promise of originality:
//I promise that this source code file has, in it's entirety, been written
//by myself and by no other person or persons. If at any time an exact copy
//of this source code is found to be used by another person in this term,
//I understand that both myself and the student that submitted the copy will 
//receive a zero on this assignment.
//


#include<stdio.h>
#include<stdlib.h>
int main(int argc, char **argv)
{
	printf("\nAssignment: 1 by Bryan Edman\n");

	printf("Shows passed in arguments, Hopefully!\n\n");
	//grabs the number of original arguments that were passed in
	//before it's changed in the while loop.
	
	int index = argc; 
       	int i = 0;

	while(argc--){
	       printf("Argument # %i", i); 	
		printf(" %s\n", *argv++);
		i++;
	}

	
	printf("\n%i", index);
	printf(" Arguments printed\n\n");
	exit(EXIT_SUCCESS);

}

