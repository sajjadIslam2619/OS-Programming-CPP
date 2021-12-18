#include <stdio.h>
#include <stdlib.h>

/*
@Author: Sajjad Islam
@Description: Print in file.
*/

int main()
{
    FILE * file;
    file = fopen("Output.txt", "w");
    if(file == NULL)
    {
        printf("Unable to create file.\n");
        return 0;
    }
    
    for (int i = 0; i <=100; i++)
    {
        fprintf(file,"%d \n", i);
    }
    fclose(file);
    printf("File created and saved successfully.\n");
    
    return 0;
}
