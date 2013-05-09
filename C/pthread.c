/* 
 * File:   pthread.c
 * Author: thura
 *
 * Created on January 22, 2009, 2:09 PM
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * a example for multithreading in C from http://softpixel.com/%7Ecwright/programming/
 */
int main(int argc, char** argv) {

    pthread_t pth;      //this is our thread identifier
    int i = 0;

    /* Create worker thread */
    pthread_create(&pth,NULL,threadFunc,"processing ...");

    /* Wait for our thread to finish before continuing */
    pthread_join(pth,NULL);

    while( i < 10)
    {
        usleep(1);
        printf("Main is running ... \n");
        ++i;
    }
    return (EXIT_SUCCESS);
}

void *threadFunc(void *arg)
{
    char *str;
    int i = 0;

    str = (char*) arg;

    while(i < 10)
    {
        usleep(1);
        printf("threadFunc says: %s\n",str);
        ++i;
    }
    return NULL;
}

