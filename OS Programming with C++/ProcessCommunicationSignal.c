//
//  main.c
//  ProcessCommunication
//
//  Created by Sajjad Islam on 10/7/21.
//

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void sighup();
void sigint();
void sigquit();

void main()
{
    int pid;
    //pid = fork();
    signal(SIGHUP, sighup);
    signal(SIGINT, sigint);
    signal(SIGQUIT, sigquit);

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        while (1){
            //infinite loop in child process
        }
    }

    else {
        signal(SIGHUP, sighup);
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
        
        printf("PARENT: sending SIGHUP to child process.\n");
        kill(pid, SIGHUP);
        sleep(5);
        
        printf("PARENT: sending SIGINT to child process.\n");
        kill(pid, SIGINT);
        sleep(5);
        
        printf("PARENT: sending SIGQUIT to child process.\n");
        kill(pid, SIGQUIT);
        sleep(5);
    }
}

void sighup() {
    signal(SIGHUP, sighup); /* reset signal */
    printf("CHILD: I have received a SIGHUP\n");
}

void sigint(){
    signal(SIGINT, sigint); /* reset signal */
    printf("CHILD: I have received a SIGINT\n");
}

void sigquit(){
    printf("CHILD: I have received a SIGQUIT\n");
    exit(0);
}
