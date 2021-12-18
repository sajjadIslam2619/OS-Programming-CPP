//
//  main.c
//  ProcessCommunicationPipe
//
//  Created by Sajjad Islam on 11/11/21.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    int fd[2]; //fd[0] - read, fd[1] - write
    char fileInputBuffer[1024];
    char fileOutputBuffer[1024];
    
    if (pipe(fd) == -1) {
        printf("An error occured while opening the pipe! \n");
        return 1;
    }
    
    int pid = fork();
    if (pid == -1) {
        printf("An error occured while calling the fork! \n");
        return 2;
    } else if (pid == 0) {
        close(fd[0]);
        /*int x;
        printf("Input a number :");
        scanf("%d", &x);
        if (write(fd[1], &x, sizeof(x)) == -1) {
            printf("An error occured while writing!!\n");
            return 3;
        }*/
        //FILE *file = fopen("/users/sajjadislam/Documents/Data.txt", "r");
        FILE *file = fopen("Data.txt", "r");
        if(file == NULL) {
            perror("Error opening file");
            return 3;
        }
        
        if( fgets (fileInputBuffer, 1024, file)!= NULL ) {
            printf("File read from 'Child process' : Input file contains bellow text. \n");
            puts(fileInputBuffer);
            if (write(fd[1], &fileInputBuffer, sizeof(fileInputBuffer)) == -1) {
                printf("An error occured while writing!!\n");
                return 4;
            }
        }
        close(fd[1]);
    } else {
        close(fd[1]);
        /*int y;
        if (read(fd[0], &y, sizeof(int)) == -1) {
            printf("An error occured while reading!!\n");
            return 4;
        }
        close(fd[0]);
        printf("Got from child process: %d \n", y*4);*/
        
        if (read(fd[0], &fileOutputBuffer, 1024) == -1) {
            printf("An error occured while reading!!\n");
            return 4;
        }
        printf("Data read from 'Parent Process' : \n");
        
        for(int i=0;i<strlen(fileOutputBuffer);i++){
            if (isupper(fileOutputBuffer[i])) {
                fileOutputBuffer[i] = tolower(fileOutputBuffer[i]);
            } else {
                fileOutputBuffer[i] = toupper(fileOutputBuffer[i]);
            }
        }
        printf("Converted Data : \n");
        printf("%s \n",fileOutputBuffer);
        close(fd[0]);
    }
    
    return 0;
}
