//
//  main_process.c
//  OperatingSystem
//
//  Created by Sajjad Islam on 9/27/21.
//

#include "main_process.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include "thread_function.h"


extern void *count_lines(void *thread_file_args);

struct thread_file_arg_struct {
    FILE *file;
    const char *filename;
};

int main() {
    pthread_t thread_id;
    struct thread_file_arg_struct thread_file_args;
    thread_file_args.filename = "Data.txt";
    
    if ((thread_file_args.file = fopen(thread_file_args.filename,"r")) == NULL){
        printf("Error! opening file");
        exit(1);
    } else {
        printf("File read successfully!!\n");
    }
    
    printf("Process will sleep for 2 second.\n");
    sleep(2);
    
    int return_code;
    void* total_line;
    
    return_code = pthread_create(&thread_id, NULL, count_lines, (void *) &thread_file_args);
    pthread_join(thread_id, &total_line);
    
    printf("Number of line in the file 'Data.txt':: %d\n\n", (void*) total_line);
    
    if (return_code) {
        printf("Error:unable to create thread, %d\n", return_code);
        exit(-1);
    }
    
    return 0;
}


