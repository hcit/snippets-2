#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

#define HOSTNAME "www.upm.edu.my"
#define SERVICE  "http"

int main(int argc, char *argv[])
{
    int status;
    struct addrinfo *hints, *results, *p;
    char ipstr[INET6_ADDRSTRLEN];

    if(argc != 2) {
        fprintf(stderr, "usage: showip hostname\n");
        exit(EXIT_FAILURE);
    }

    hints = (struct addrinfo*)malloc(sizeof (struct addrinfo));
    memset(hints, 0, sizeof hints);
    hints->ai_family    = AF_UNSPEC;    //Either AF_INET or AF_INET6
    hints->ai_socktype  = SOCK_STREAM;

    if((status = getaddrinfo(argv[1]/*HOSTNAME*/, NULL/*SERVICE*/, hints, &results)) == -1) {
        fprintf(stderr,"getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    for(p = results; p != NULL; p = p->ai_next) {
        void *addr;
        if(p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4  = (struct sockaddr_in *) p->ai_addr;
            addr = &(ipv4->sin_addr);
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
            addr = &(ipv6->sin6_addr);
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("IP: %s\n", ipstr);
    }

    exit(EXIT_SUCCESS);
}