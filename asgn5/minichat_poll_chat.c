#include "minichat.h"
#include <poll.h>

#define LOCAL  0
#define REMOTE (LOCAL + 1)

void chatclient(int sockfd) {
   int done, len, mlen;
   char buff[MAXLINE];
   struct pollfd fds[REMOTE+1];

   fds[LOCAL].fd = STDIN_FILENO;
   fds[LOCAL].events = POLLIN;
   fds[LOCAL].revents = 0;
   fds[REMOTE]=fds[LOCAL];
   fds[REMOTE].fd = sockfd;

   done = 0;
   do {

      poll(fds,sizeof(fds)/sizeof(struct pollfd),-1); /* negative->wait forever */
      if (fds[LOCAL].revents & POLLIN ) {
         /* read a line and send it to remote */
         len = read(STDIN_FILENO,buff,MAXLINE);
         mlen=send(sockfd, buff, len, 0);
      }
      if (fds[REMOTE].revents & POLLIN ) {
         /* receive a line and print it */
         mlen = recv(sockfd, buff, sizeof(buff),0);

         write(STDOUT_FILENO,buff,mlen);
      }
      if ( !strncmp(buff,"bye",3) )
         done = 1;
   } while (!done);
}