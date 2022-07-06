#include "minichat.h"
#include <poll.h>

#define LISTENER 0
void chatserver(int listener) {
   int i,j, done, mlen, newsock, num = 0;
   struct sockaddr_in peerinfo;
   socklen_t slen;
   char buff[MAXLINE],addr[INET_ADDRSTRLEN];
   struct pollfd fds[MAX_CONNECTIONS + 1];

   done = 0;

   fds[LISTENER].fd = listener;
   fds[LISTENER].events = POLLIN;
   fds[LISTENER].revents = 0;
   num = 1;

   do {
      if ( -1 == poll(fds,num,-1) ) {
         perror("poll");
      }

      /* check for connections */
      if ( (fds[LISTENER].revents & POLLIN) && ( num <= MAX_CONNECTIONS )) {
         /* accept a new connection and add the client to the list */
         slen = sizeof(peerinfo);
         newsock = accept(listener, (struct sockaddr *)&peerinfo, &slen);

         inet_ntop(AF_INET, &peerinfo.sin_addr.s_addr,addr, sizeof(addr));
         printf("New connection from: %s:%d\n", addr, htons(peerinfo.sin_port));
         fds[num].fd     = newsock;
         fds[num].events = POLLIN;
         fds[num].revents = 0;
         num++;
      }
      /* check for data */
      for(i=1;i<num;i++) {
         if ( fds[i].revents & POLLIN ) {
            /* read from this client and broadcast to all */
            slen = sizeof(struct sockaddr_in);
            mlen = recv(fds[i].fd, buff, sizeof(buff),0);

            for(j=1;j<=num;j++)          /* broadcast to everyone else*/
               if ( i != j )      /* not self */
                  send(fds[j].fd, buff, mlen, 0);
         }
      }
      if ( !strncmp(buff,"bye",3) )
         done = 1;
   } while (!done);
}