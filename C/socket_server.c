/*
 * File:   socket_client.c
 * Author: thura
 *
 * Created on February 6, 2009, 1:11 PM
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

#define HOSTNAME "localhost"
#define SERVICE  "http"
#define PORT     "9998"
#define NSTRS    3

char *str[NSTRS] = {
    "This is the first string from the server.\n",
    "This is the second string from the server.\n",
    "This is the third string from the server.\n"
};

int main(int argc, char *argv[])
{
    FILE *fp;
    register int sockfd, client_sockfd;
    char c; int i; int status;
    struct addrinfo *addr_info, *client_addr_info;
    int len, client_len = '\0';


    addr_info = (struct addrinfo *)malloc(sizeof(struct addrinfo));
    if((status = getaddrinfo(HOSTNAME, PORT/*SERVICE*/, NULL/*HINTS*/, &addr_info)) == -1) {
        fprintf(stderr,"getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }


    if((sockfd = socket(addr_info->ai_family,addr_info->ai_socktype,addr_info->ai_protocol)) == -1) {
        perror("socket error:");
        exit(EXIT_FAILURE);
    }

    unlink(HOSTNAME);
    if((bind(sockfd,addr_info->ai_addr, addr_info->ai_addrlen)) == -1) {
        perror("bind error:");
        exit(EXIT_FAILURE);
    }

    if((listen(sockfd,5)) == -1) {
        perror("listen error:");
        exit(EXIT_FAILURE);
    }

    client_addr_info = (struct addrinfo *)malloc(sizeof(struct addrinfo));
    if((client_sockfd = accept(sockfd, client_addr_info->ai_addr, (socklen_t *)client_addr_info->ai_addrlen)) == -1) {
        perror("accept error:");
        exit(EXIT_FAILURE);
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

    fclose(fp);
    close(sockfd);
    return(EXIT_SUCCESS);
}