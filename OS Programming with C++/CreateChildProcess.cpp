#include<stdio.h>
#include <unistd.h>

/*
@Author: Sajjad Islam
@Description: UNIX program that creates a child process
*/

int main () 
{
	int child = fork();
	
	if (child > 0) 
	{
		printf("Parent process is executing.\n");
		printf("Parent process ID :  %d \n ", getpid());
		printf("Parent of parent process ID : %d \n", getppid());
	}
	
	else if (child == 0)
	{
		printf ("Child process is executing.\n");
		printf("Child Process ID : %d \n ", getpid());
	}
    
    printf("HHH %d \n", getpid());
	
	return 0;
}
