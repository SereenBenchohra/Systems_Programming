#include "fileHandle.h"
#include "split.h"

void integer_error(char *notNum)
{
    fprintf(stderr, "\"%s\" is not an integer\n", notNum);
    fprintf(stderr, "Usage error: [integer][file_system]\n");
    exit(EXIT_FAILURE);
}

/* is integer program checks for the string whether it is an integer or not
the program loops through each character to
check if its a digit or not */

int is_integer(char *isNum)
{
    int num;

    char *end, *local;
    local = isNum;
    num = strtol(local, &end, 10);
    // if not raise error
    if(end == local || num < 0)
        integer_error(isNum);

    return num;
}

int verify_arguments(int argc, char *argv[])
{

    int num;
    if(argc != VALID_ARGUMENTS)
    {
        fprintf(stderr, "Improper number arguments \n");
        exit(EXIT_FAILURE);
    }

    num = is_integer(argv[1]); // check if valid integer if so, store in inode struct
    return num;
}


FILE *open_file(const char *path, const char *mode)
{
    FILE *file;
    if((file = fopen(path, mode)) == NULL)
    {
        perror(path);
        exit(EXIT_FAILURE);
    }
    return file;
}

int get_array_length(FILE *file)
{
    int len = 0;
    char *line = NULL;
    size_t size = 0;

    while(getline(&line, &size, file) > 0)
        len++;

    rewind(file); // resets file to begginning

    free(line);
    return len;

}
// function to free list and its allocated strings and nodes
void free_list(Down_Info **list, int len)
{
    for(int i = 0; i < len; i++)
    {
        free(list[i]->filename);
        free(list[i]->URL);
        if (list[i]->sec != NULL)
            free(list[i]->sec);
        free(list[i]);
    }

    free(list);

}

Down_Info *create_Down_Info( char *filename, char *URL, char *sec) // create a download info node
{
    Down_Info *down = NULL;
    if ((down = malloc(sizeof(Down_Info))) == NULL)
    {
        perror("down");
        exit(EXIT_FAILURE);
    }

    down->filename = strndup(filename, strlen(filename));

    int len = strlen(URL);
    if(URL[len -1] == '\n')
        down->URL = strndup(URL, len - 1); // dont write the '\n' to stream
    else
        down->URL = strndup(URL, len);

    if (sec != NULL)
        down->sec = strndup(sec, strlen(sec) - 1);
    else
        down->sec = NULL;

    return down;
}

// function to store data within file req 2)
Down_Info **retrieve_data(FILE *file, int array_len )
{
    int len = 0;
    char *line = NULL;
    char **tokens = NULL;
    size_t size = 0;
    Down_Info **download_list = NULL;
    download_list = malloc(sizeof(Down_Info* ) *array_len);

    while(getline(&line, &size, file) > 0)
    {
        tokens = split(line);
        Down_Info *down  = create_Down_Info(tokens[0], tokens[1], tokens[2]);
        download_list[len++] = down;
        free(tokens);
    }

    free(line);
    return download_list;

}




