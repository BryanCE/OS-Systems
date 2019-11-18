#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include<sys/wait.h>
#include<stdlib.h> 

//Bryan Edman
//CS3060-001
//Assignment: 2
//Promise of Originality
//I promise that this source code file has, in its entirety, been
//written by myself and by no other person or persons. If at any time an 
//exact copy of this source code is found to be used by another person 
//in this term, I understand that both myself and the student that 
//submitted the copy will recievee a zero on this assignment

int main(int argc, char **argv )
{
/*pid is some data*/
pid_t pid;
/* fork a child process */ 
	 pid = fork();
	
	 	
	if (pid <0) {
		fprintf(stderr, "Fork Failed");
		return 1;
	}

	else if(pid == 0) {
		char *arguments[argc];

		int i = 0;
		//grabbing the arguments from the CLI
		for(i = 0; i < argc; i++)
		{
			arguments[i] = argv[i +1];
		}
		
		if(argc == 1)
		{
			printf("\nChild started, no arguments provided. Child Terminating\n");

		}
		else if(argc == 2)
		{
			printf("\nChild started, One argument provided. using execlp()\n");
			execlp(argv[1], argv[1],NULL);
			perror("Something went wrong using execlp()!!!");
		}
		else
		{
			printf("\nChild started, More than one argument. Using execvp()\n");
			execvp(argv[1], arguments);
			perror("Something went wrong using execvp()!!!");
		}

	}
	else {
		/* parent will wait for the child to complete */
		printf("\nParent started, waiting for process ID#%d \n", pid);
		//wait(NULL);
		int retrn = 0;
		wait(&retrn); 
		printf("\nParent resumed. Child exit code: %d. Now terminating parent\n\n", WEXITSTATUS(retrn)); 
	}
	return 0;
}
