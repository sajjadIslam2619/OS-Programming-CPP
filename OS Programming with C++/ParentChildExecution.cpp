#include<stdio.h>
#include <unistd.h>
#include<sys/wait.h>

/*
@Author: Sajjad Islam
@Description: Parent process wait for child process execution.
*/

int main () 
{
	int child = fork(); 
	//int child =  vfork(); //vfork() function can be used to execute child process first.
	
	int pid_child;
    int status_child;
	
	if (child > 0) 
	{
		printf("Parent process is executing.\n");
		printf("Parent process ID :  %d \n", getpid());
		int even_sum = 0;
		for (int i = 0; i <=1000 ; i++)
		{
			if (i%2==0)
			{
				even_sum = even_sum + i;
			}
		}
		printf("Parent process : sum of even number :  %d \n", even_sum);
		printf("Parent process is waiting for child process execution!!\n");

		//int id = waitpid(pid_child, &status_child, WNOHANG); // if id=0 then child process is still running; if id=pid_child then child process execution is completed.
		
		int id = waitpid(pid_child, &status_child, 0); //waiting for child process to finish. 
		
		//sleep(5); //sleep() function also can be used to sleep the parent procss and process the child process first. 
		
		printf("Parent process execution done!!\n");
	}
	
	else if (child == 0)
	{
		printf ("Child process is executing.\n");
		printf("Child Process ID : %d \n", getpid());
		pid_child = getpid();
		
		int odd_sum = 0;
		for (int i = 0; i <=1000 ; i++)
		{
			if (i%2 !=0)
			{
				odd_sum = odd_sum + i;
			}
		}
		printf("Child process : sum of odd number :  %d \n", odd_sum);
		printf("Child process execution done!!\n");
	}
	
	return 0;
}
