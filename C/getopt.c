#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int aflag,bflag = 0;
    char *cvalue = NULL;

    int index;
    int c;

    /*
     * If the value of opterr is nonzero,
     * then getopt prints an error message to the standard error stream
     * if it encounters an unknown option character or an option with a missing required argument.
     */
    opterr = 0;

    while(( c = getopt(argc,argv,"abc:")) != -1) {
        switch(c) {
            case 'a':
                aflag = 1;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'c':
                //This variable is set by getopt to point at the value of the option argument
                cvalue = optarg;
                break;
            case '?':
                /*
                 *When getopt encounters an unknown option character/an option with a missing required argument,
                 * it stores that option character in optopt variable.
                 */
                if(optopt == 'c')
                    fprintf(stderr,"Option -%c requires an argument.\n",optopt);
                else if (isprint(optopt))
                    fprintf(stderr,"Unknown option`-%c'.\n",optopt);
                else    //For non-printable characters
                    fprintf(stderr,"Unknown option character `\\x%x'.\n",optopt);
                return 1;
            default:
                abort();
        }
    }

    printf("aflag = %d, bflag = %d, cvalue = %s\n",
            aflag, bflag, cvalue);

    /*optind is set by getopt to the index of the next element of the argv array to be processed.
     * Once getopt has found all of the option arguments,
     * you can use this variable to determine where the remaining non-option arguments begin.
     */
    printf("argc --> %d",argc);
    printf("optind --> %d \n", optind);
    for(index = optind; index < argc; index++)
        printf("Non-option argument %s <- %d\n", argv[index], optind);
    return 0;
}
