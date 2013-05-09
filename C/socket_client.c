/*
 * File:   socket_client.c
 * Author: thura
 *
 * Created on February 6, 2009, 1:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netdb.h>

#define NSTRS      3
#define HOSTNAME  "localhost"
#define PORT      "9998"

char *str[NSTRS] = {
    "This is the first string from the client.\n",
    "This is the second string from the client.\n",
    "This is the third string from the client.\n"
};

int main(int argc, char** argv) {

    FILE *fp;
    register int i, sockfd;
    int status; char c;
    struct addrinfo *addr_info, *server_addr_info;

    addr_info = (struct addrinfo *)malloc(sizeof(struct addrinfo));
    if((status=getaddrinfo(HOSTNAME,NULL,NULL,&addr_info)) == -1) {
        fprintf(stderr,"getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    if((sockfd = socket(addr_info->ai_family, addr_info->ai_socktype, addr_info->ai_protocol)) == -1) {
        perror("socket error: ");
        exit(1);
    }

    server_addr_info = (struct addrinfo *)malloc(sizeof(struct addrinfo));
    if((status=getaddrinfo(HOSTNAME,PORT,NULL,&server_addr_info)) == -1) {
        fprintf(stderr,"getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }
    
    if(connect(sockfd, server_addr_info->ai_addr, server_addr_info->ai_addrlen) == -1)  {
        perror("connect error: ");
        exit(1);
    }

    fp = fdopen(sockfd, "r");
    for(i = 0; i < NSTRS; i++) {
        while((c= fgetc(fp)) != EOF) {
            putchar(c);
            if(c == '\n')
                break;
        }
    }

    for(i = 0; i <NSTRS; i++)
        send(sockfd,str[i], strlen(str[i]),0);

    close(sockfd);
    return (EXIT_SUCCESS);
}

