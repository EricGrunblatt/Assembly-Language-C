#include <stdlib.h>
#include <stdio.h> 
#include <getopt.h>
#include <flags.h>

extern int orig_main(int argc, const char *const *argv);

int main(int argc, const char *const *argv) {
    int c;

    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
        {"help",     no_argument, 0,  'h' },
        {"output-directory", required_argument,       0,  'O' },
        {"no-second-pass",    no_argument, 0,  '2' },
    };
    if(argc <= 1) {
        exit(EXIT_FAILURE);
    }

    c = getopt_long(argc, (char *const *) argv, "h2O:", long_options, &option_index);

    optIndex = optind;

    switch (c) {
        case 'h':
            // USAGE STATEMENT
            fprintf(stderr, "USAGE: %s\n", \
            "[-h|-2|-O] [DIR/]\n" \
            "   -h       --help: displays this help menu.\n" \
            "   -2       --no-second-pass: the program runs through the file once and exits.\n" \
            "No arguments should follow this.\n" \
            "   -O       --output-directory: the program reads and writes terms to a specified output path.\n" \
            "The following must contain an output directory following the format DIR/ where DIR can be any folder name\n" \
            );
            break;
        
        case 'O':
            // MAKE SURE ARG ENDS IN '/'
            outputFile = optarg;
            mainFlag = 'O';
            orig_main(argc, argv);
            break;

        case '2':
            mainFlag = '2';
            orig_main(argc, argv);
            break;

        case '?':
            break;

        default:
            fprintf(stderr, "?? getopt returned character code 0%o ??\n", c);
        }

   if (optind < argc) {
        fprintf(stderr, "non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        fprintf(stderr, "\n");
    }

   exit(EXIT_SUCCESS);
}
