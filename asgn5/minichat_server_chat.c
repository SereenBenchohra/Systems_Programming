#include "minichat.h"

void chatserver(int listener) {
  int clients[MAX_CONNECTIONS];
  int max,i,j, done, mlen, newsock, num_clients = 0;
  fd_set readfds;
  struct sockaddr_in peerinfo;
  socklen_t slen;
  char buff[MAXLINE],addr[INET_ADDRSTRLEN];

  done = 0;
  do {
    FD_ZERO(&readfds);
    FD_SET(listener,&readfds);
    max = listener;
    for(i=0;i<num_clients; i++) {
      FD_SET(clients[i],&readfds);
      if ( clients[i] > max )
        max = clients[i];
    }
    select(max+1,&readfds,NULL,NULL,NULL); /* wait for it... */

    if (FD_ISSET(listener,&readfds) && ( num_clients < MAX_CONNECTIONS - 1 )) {
      /* accept a new connection and add the client to the list */
      slen = sizeof(peerinfo);
      newsock = accept(listener, (struct sockaddr *)&peerinfo, &slen);

      inet_ntop(AF_INET, &peerinfo.sin_addr.s_addr,addr, sizeof(addr));
      printf("New connection from: %s:%d\n", addr, htons(peerinfo.sin_port));
      clients[num_clients++] = newsock;
    } else {
      for(i=0;i<num_clients;i++) {
        if ( FD_ISSET(clients[i],&readfds) ) {
          /* read from this client and broadcast to all */
          slen = sizeof(struct sockaddr_in);
          mlen = recv(clients[i], buff, sizeof(buff),0);

          for(j=0;j<num_clients;j++)          /* broadcast to everyone else*/
            if ( i != j )      /* not self */
              send(clients[j], buff, mlen, 0);
        }
      }
    }
    if ( !strncmp(buff,"bye",3) )
      done = 1;
  } while (!done);
}
