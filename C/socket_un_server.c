/* 
 * File:   socket_server.c
 * Author: thura
 *
 * Created on February 6, 2009, 3:15 AM
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h> //For AF_UNIX
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NSTRS   3
#define ADDRESS "localhost"

char *str[NSTRS] = {
    "This is the first string from the server.\n",
    "This is the second string from the server.\n",
    "This is the third string from the server.\n"
};


int main(int argc, char** argv) {

    FILE *fp;
    register int sockfd, client_sockfd;int len;
    char c;
    int i;
    int flen = NULL;
    struct sockaddr_un sa_un, fsa_un;

    /* int socket (int domain, int type, int protocol)
     * domain --> AF UNIX: address format is UNIX pathname, or
     *            AF INET: address format is host and port number
     * type   --> SOCK_STREAM:    use TCP, sequenced, reliable, unduplicated flow-controlled
     *            SOCK_DGRAM:     use UDP,
     *            SOCK_SEQPACKET: maximum massage size, not avalaible on most machines
     * protoc0l--> 0 for any protocol
     */
    if((sockfd= socket(AF_UNIX,SOCK_STREAM,0)) < 0) {
        perror("server: socket");
        exit(1);
    }

    sa_un.sun_family = AF_UNIX;
    strcpy(sa_un.sun_path, ADDRESS);

    unlink(ADDRESS);
    len = sizeof(sa_un.sun_family) + strlen(sa_un.sun_path);

    /* int bind(int sockid, struct sockaddr *addrPtr, int len) */
    if(bind(sockfd, (struct sockaddr*)&sa_un,len) < 0) {
        perror("server: bind");
        exit(1);
    }

    /* int listen(int sockid, int size)
     * size is typically limited to 5 by Unix Kernels */
    if(listen(sockfd, 5) < 0) {
        perror("server: listen");
        exit(1);
    }

    /* int accept(int sockid, struct sockaddr *addrPtr, int *lenPtr)
     * Return the sockid of the client */
    if((client_sockfd = accept(sockfd, (struct sockaddr*)&fsa_un, &flen)) < 0) {
        perror("server: accept");
        exit(1);
    }

    fp = fdopen(client_sockfd,"r");

    for (i = 0; i < NSTRS; i++)
        send(client_sockfd, str[i], strlen(str[i]), 0);


    for(i = 0; i < NSTRS; i++) {
        while((c = fgetc(fp)) != EOF) {
            putchar(c);
            if( c == '\n')
                break;
        }
    }

    close(sockfd);
    return (EXIT_SUCCESS);
}

