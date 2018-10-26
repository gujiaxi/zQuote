#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "zquote.h"
#include "qcard.h"

int show_help_msg()
{
    printf("zquote: make fancy quote cards.\n\n");
    printf("Usage:\n\tzquote -b BODY [options]\n");
    printf("Options:\n");
    printf("\t-i, --interactive       Enter interactive mode.\n");
    printf("\t-b, --body BODY         Specify quote body.\n");
    printf("\t-t, --title TITLE       Specify quote title.\n");
    printf("\t-a, --author AUTHOR     Specify quote author.\n");
    return 0;
}

int main(int argc, char *argv[])
{
    int c;
    char * body = NULL;
    char * title = NULL;
    char * author = NULL;
    size_t size;
    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"interactive", optional_argument, 0, 'i'},
            {"body",    required_argument, 0, 'b' },
            {"title",   required_argument, 0, 't' },
            {"author",  required_argument, 0, 'a' }
        };

        c = getopt_long(argc, argv, "ib:t:a:",
                        long_options, &option_index);
        if (c == -1) {
            break;
        }

        switch (c) {
        case 'i':
            printf("BODY (Required):\n");
            getline(&body, &size, stdin);
            printf("TITLE (Optional):\n");
            getline(&title, &size, stdin);
            printf("AUTHOR (Optional):\n");
            getline(&author, &size, stdin);
            break;
        case 'b':
            body = optarg;
            break;
        case 't':
            title = optarg;
            break;
        case 'a':
            author = optarg;
            break;
        default:
            break;
        }
    }

    if (!body) {
        show_help_msg();
        exit(-1);
    } else make_quote_img(body, title, author);

}
