/*
 * C Program Delete a specific Line from a Text File
 */
#include <stdio.h>
#include <stdlib.h>

void remove_line()
{
    FILE *fileptr1, *fileptr2;
    int delete_line = 2;
    int count = 1;

    //open file in read mode
    fileptr1 = fopen("cprogramming.txt", "r");

    char *line = NULL;
    size_t size = 0;

    //open new file in write mode
    fileptr2 = fopen("temp.txt", "w");
    printf("%d\n", delete_line);

    while(getline(&line, &size, fileptr1) > 0)
    {
        if(count != delete_line)
            fputs(line, fileptr2);
        count++;
    }


    free(line);
    fclose(fileptr1);
    fclose(fileptr2);
    remove("cprogramming.txt");
    //rename the file replica.c to original name
    rename("temp.c", "cprogramming.txt");  //rename the file replica.c to original name
}


int main()
{

    remove_line();

    return 0;
}

