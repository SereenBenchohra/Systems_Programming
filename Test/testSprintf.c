include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split(char *string)
{
    char **StringList;
    StringList = NULL;
    char *local, *tokens;
    local = tokens = NULL;
    int len = 0, i; 
    local = string;
    tokens = strtok (local, " ");

    while(tokens) /* split string and append tokens to 'StringList' */
    {
        StringList = realloc (StringList, sizeof (char*) * ++len);
        if(StringList == NULL)
        {
            perror(*StringList);
            exit(EXIT_FAILURE);
        }
        StringList[len - 1] = tokens;  
        tokens = strtok (NULL, " ");      
    }

    /* realloc one extra element for the last NULL */

    StringList = realloc (StringList, sizeof (char*) * (len+1));
    StringList[len] = 0;

/* print the result */

    return StringList;

}

int main()
{
    char *str = "ls -l";
    char *local;
    local = NULL;
    local = strdup(str);

    char **res;
    res = NULL;
    res  = split(local);
    int i;

    for (i = 0; res[i] != NULL; ++i)
        printf ("StringList[%d] = %s\n", i, res[i]);


    free(local);
    free(res);

    return 0;
}�