#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

/* Flag set by --verbose */
static int verbose_flag;

int main (argc, argv)
    int argc;
    char **argv;
{
    int c = NULL;

    while(1)
    {
        /*The struct option structure has these fields
         *      const char *name = a string which represents the name of the string
         *      int has_arg      = an integer, which could be one of no_argument, required_argument and optional_argument.
         *      int *flag
         *      int val
         *      If flag pointer is null, then the value is the value which identifies this option
         *      If not, it should be the address of an int variable which is the flag for this option         *
         */
        static struct option long_options[] =
        {
            /*These options set a flag */
            {"verbose", no_argument, &verbose_flag, 1},
            {"brief", no_argument, &verbose_flag, 0},
            /*These ones don't set a flag.
             *We distinguish them by their indices */
            {"add",     no_argument,        0, 'a'},
            {"append",  no_argument,        0, 'b'},
            {"delete",  required_argument,  0, 'd'},
            {"create",  required_argument,  0, 'c'},
            {"file",    required_argument,  0, 'f'},
            {0, 0, 0, 0}
        };

        int option_index = 0;

        //int getopt_long (int argc, char *const *argv, const char *shortopts, const struct option *longopts, int *indexptr)
        c = getopt_long(argc,argv,"abc:d:f:",long_options,&option_index);

        //As getopt_long returns -1 on end of option
        if( c == -1)
            break;

        switch(c)
        {
            case 0:
                /* If this option set a flag, do nothing else now. */
                if(long_options[option_index].flag != 0)
                    break;
                printf("Option %s", long_options[option_index].name);
                if(optarg)
                    printf(" with arg %s", optarg);
            case 'a':
                puts("option -a");
                break;

            case 'b':
                puts("option -b");
                break;

            case 'c':
                printf("option -c with value `%s'\n", optarg);
                break;

            case 'd':
                printf("option -d with value `%s'\n", optarg);
                break;

            case 'f':
                printf("option -f with value `%s'\n", optarg);
                break;
            case '?':
                /* getopt_long already printed an error message. */
                break;
            default:
                abort();
        }
    }
    if(verbose_flag)
        puts("verbose flag is set");
    if(optind < argc)
    {
        printf("Non-option ARGV-elements: ");
        while(optind < argc)
            printf("%s", argv[optind++]);
        putchar('\n');
    }
    exit(EXIT_SUCCESS);
}
