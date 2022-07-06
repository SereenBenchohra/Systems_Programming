CC = gcc

CFLAGS = -Wall -g -Og

all: pclient pserver mytalk

mytalk: client.c client_main.c minichat.h server.c server_main.c mytalk.c
	$(CC) -o $@ $(CFLAGS) client.c client_main.c server.c server_main.c mytalk.c

pclient: minichat_client_main.c minichat_poll_chat.c minichat.h
	$(CC) -o $@ $(CFLAGS) minichat_client_main.c minichat_poll_chat.c

pserver: minichat_server_main.c minichat_poll_server.c minichat.h
	$(CC) -o $@ $(CFLAGS) minichat_server_main.c minichat_poll_server.c

clean:
	-rm  pclient pserver client server 

