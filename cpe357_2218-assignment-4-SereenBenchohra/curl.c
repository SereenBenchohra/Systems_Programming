#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#include <stdlib.h>
#include "fileHandle.h"
#include "processHandle.h"


int main(int argc, char *argv[])
{

    // req 1
    int maxDown = verify_arguments(argc, argv);
    FILE *file = open_file(argv[2], "r");

    // req 2 (done)
    int array_len = get_array_length(file);
    Down_Info **download_list = retrieve_data(file, array_len);

    // if array_len < maxDown , fork all and run all of them simultaneously  and wait to finish
    if(array_len <= maxDown) // check array len and maxDown
        download_all(download_list, array_len );
    else
        max_exceeded(download_list, array_len, maxDown);

    free_list(download_list, array_len);
    fclose(file);
    return 0;
}


