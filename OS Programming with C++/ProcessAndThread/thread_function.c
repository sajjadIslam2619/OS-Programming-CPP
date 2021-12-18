//
//  thread_function.c
//  OperatingSystem
//
//  Created by Sajjad Islam on 9/27/21.
//

#include "thread_function.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pthread.h>
#include "main_process.h"

struct thread_file_arg_struct {
    FILE *file;
    const char *filename;
};

void *count_lines(void *thread_file_args) {
    printf("Counting line of file in a separate thread.\n");
    struct thread_file_arg_struct *args = (struct thread_file_arg_struct *) thread_file_args;
    
    struct stat sb;
    if (stat(args -> filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char *file_contents = (char*) malloc(sb.st_size);
    long num_of_line = 0;
    while (fscanf(args -> file, "%[^\n] ", file_contents) != EOF) {
        num_of_line++;
        //printf("> %s\n", file_contents);
    }
    fclose(args -> file);
    
    return (void*)num_of_line;
}


