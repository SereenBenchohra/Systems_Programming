#include "minichat.h"
#include <ctype.h>
void chatclient(int sockfd);



int myatoi(char *s) {
   int res = 0, minus = *s == '-';
   if (minus) s++;

   while (isdigit(*s)) {
      res = res*10 + (*s++ - '0');
   }

   return minus ? -res : res;
}

void client_init(char *hostname, char *portName)
{
   int sockfd;                   /* socket descriptors */
   struct sockaddr_in sa;
   struct hostent  *hostent;
   int port;

   /* check if port is formatted correctly otherwise raise perror and usage*/
   port = atoi(portName);

   /* figure out who we're talking to */
   hostent = gethostbyname(hostname);
   if(!hostent)
   {
      perror("gethostbyname");
      exit(EXIT_FAILURE); /* is this a failure ? */
   }

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
}

