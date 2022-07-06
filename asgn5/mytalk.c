#include "minichat.h"

// #include "include/talk.h"

/* to do tomorrow :
 * get server to talk to client 
 * get server to talk to client
 * start window
 * read from input 
 * write to output 
 * base it off from polling and Nico's slides
*/

void UsageError()
{
    fprintf(stderr, "mytalk [ -a ] [ -N ] [ -v ] [ hostname ] port\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    /* check optional arguments are there */ 
    /*if not then raise error */
    
    if(argc < 2)
       UsageError();
    else if ( argc==2 ) /* no host name given  got to server*/
      server_init(argv[1]);
    else if(argc == 3) /* if there is a hostname go to client */
      client_init(argv[1], argv[2]);
   /* check if there is a hostname given */
    /* if there is none treat as server */
    /* otherwise initialize client */
// void start_windowing(void);
// while()
 //  void stop_windowing(void);
    /* if there is a hostname go to client and run client */

    /* otherwise run server */ 
  
    return 0; 
} 