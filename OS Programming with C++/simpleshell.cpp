//  Course: COSC4302
//  Project info: Simple Shell (Ex: 2.1)
//  Created by Sajjad Islam on 11/23/21.

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

#define PARAMTSIZE 255
#define MAXARGS 63
#define PIDBUFFER 5
#define LINE_LEN 80

void printPrompt(string userName);
void readCommand(char* commandLine);
void parseCommand(char *inputPtr, char *args[]);

int main(void)
{
    int status = 0;
    int pid = 0;
    int pastPid[PIDBUFFER + 1] = {0};
    int pidCounter = 0;
    
    // prepare prompt format : {user name} and shell string.
    string userName = getenv("USER");
    //string shellPrompt = userName + "_shell>";
    
    while (1) {
        char input[PARAMTSIZE + 1] = {0};
        char *inputPtr = input;
        char *args[MAXARGS + 1] = {NULL};
        string inputStr;

        // print prompt.
        printPrompt(userName);
        
        // get command from user.
        readCommand(input);

        // ignore empty input
        if (*inputPtr == '\n') continue;
        
        // convert command (input line) to list of arguments
        parseCommand(inputPtr, args);
        
        // exit the program if input/command is 'exit'
        if (strcmp("exit", args[0]) == 0) {
            exit(0);
        }
        
        // showpid : print the last 5 child process IDs created by the simpleshell
        else if (strcmp("showlatestpid", args[0]) == 0) {
            for (int i = 0; i < PIDBUFFER; i++) {
                std::cout << pastPid[i] << '\n';
            }
        }
        else {
            pid = fork();
            if (pid == -1) {
                printf("Error: Unable to create a child process!! \n");
                exit(0);
            }
            // fork child and execute command
            else if (pid == 0) {
                execvp(args[0], args);
                // notify user if command could not be executed and end child process
                printf("Error: Command could not be executed!! \n");
                exit(1);
            }
            // parent process.
            else {
                // wait for child process to execute.
                waitpid(-1, &status, 0);
                printf("Child process exit status : %d \n", status);
                
                // store child process ID
                if ((pastPid[PIDBUFFER - 1] != 0)) {
                    for (int i = 0; i < PIDBUFFER; i++) {
                        pastPid[i] = pastPid[i + 1];
                    }
                    pastPid[PIDBUFFER - 1] = pid;
                } else {
                    pastPid[pidCounter++] = pid;
                }
            }
        }
    }
}

void readCommand(char* commandLine){
    fgets(commandLine,LINE_LEN,stdin);
}

void printPrompt(string userName){
    string shellPrompt = userName + "_shell>";
    printf("%s ",shellPrompt.c_str());
}

void parseCommand (char *inputPtr, char *args[]){
    
    for (int i = 0; i < sizeof(args) && *inputPtr; inputPtr++) {
        
        if (*inputPtr == ' ') {
            continue;
        }
        
        if (*inputPtr == '\n') {
            break;
        }
        
        args[i++] = inputPtr;
        while (*inputPtr && *inputPtr != ' ' && *inputPtr != '\n') {
            inputPtr++;
        }
        *inputPtr = '\0';
    }
}
