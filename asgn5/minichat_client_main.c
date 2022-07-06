#include "minichat.h"
void chatclient(int sockfd);

int main(int argc, char *argv[]) {
  int sockfd;                   /* socket descriptors */
  struct sockaddr_in sa;
  struct hostent  *hostent;
  int port;
  char *hostname = "localhost";

  if ( argc==2 )
    port = atoi(argv[1]);
  else
    port = 10000;

  /* figure out who we're talking to */
  hostent = gethostbyname(hostname);

  /* Create the socket */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  /* connect it */
  sa.sin_family = AF_INET;
  sa.sin_port   = htons(port);                /* use our port  */
  sa.sin_addr.s_addr   = *(uint32_t*)hostent->h_addr_list[0]; /* net order */

  connect(sockfd, (struct sockaddr *)&sa, sizeof(sa));

  chatclient(sockfd);

  /* send some data */
  close(sockfd);
  return 0;
}

