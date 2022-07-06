#include "minichat.h"
#define DEFAULT_BACKLOG MAX_CONNECTIONS
#define MAX_ADDR 100
void chatserver(int sockfd);

int main(int argc, char *argv[]) {
  int sockfd;             /* socket descriptors */
  struct sockaddr_in sa;
  int port;

  if ( argc==2 )
    port = atoi(argv[1]);
  else
    port = 10000;

  /* Create the socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  /* bind it to our address*/
  sa.sin_family = AF_INET;
  sa.sin_port   = htons(port);     /* use our port  */
  sa.sin_addr.s_addr   = htonl(INADDR_ANY);   /* all local interfaces */

  bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));

  listen(sockfd,DEFAULT_BACKLOG);

  chatserver(sockfd);  /* accept connections and chat */

  /* all done, clean up */
  close(sockfd);
  return 0;
}
