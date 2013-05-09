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

#define NSTRS    3
#define ADDRESS  "localhost"

char *str[NSTRS] = {
    "This is the first string from the client.\n",
    "This is the second string from the client.\n",
    "This is the third string from the client.\n"
};

int main(int argc, char** argv) {

    char c;
    FILE *fp;
    register int i, sockfd, len;
    struct sockaddr_un sa_un;

    if((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("client: socket");
        exit(1);
    }

    sa_un.sun_family = AF_UNIX;
    strcpy(sa_un.sun_path, ADDRESS);

    len = sizeof(sa_un.sun_family) + strlen(sa_un.sun_path);
    if(connect(sockfd, (struct sockaddr*)&sa_un, len) < 0)  {
        perror("client: connect");
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

