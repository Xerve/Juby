// V 0.0.1

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "juby.h"

int main(int argc, char** argv) {
    Scope* scope = Prelude();
    if (argc == 1) {
        char input[1024];
        printf("juby> ");
        while(fgets(input, 1024, stdin)) {
            input[strlen(input) - 1] = '\0';
            if (!strcmp(input, ":quit")) { break; }
            print_Object(eval(scope, input));
            recover(true);
            memset(input, '\0', strlen(input));
            Scope__collectGarbage(scope, false);
            printf("\njuby> ");
        }
    } else {
        int i;
        for(i = 0; i < argc; ++i) {
            if (!strcmp(argv[i], "-y")) {
                if (i != argc - 1) {
                    if (argv[i + 1][0] != '-') {
                        char* buffer = 0;
                        long length = 0;
                        FILE* f = fopen(argv[i + 1], "rb");

                        if (f) {
                            fseek (f, 0, SEEK_END);
                            length = ftell(f);
                            fseek (f, 0, SEEK_SET);
                            buffer = malloc(length + 1);

                            if (buffer) {
                                fread(buffer, 1, length, f);
                            }

                           fclose(f);

                           buffer[length] = '\0';

                           if (buffer) {
                               eval(scope, buffer);
                               free(buffer);
                           }
                        } else {
                            printf("No such file: %s\n", argv[i + 1]);
                        }
                    } else {
                        puts("No input file given!");
                    }
                } else {
                    puts("No input file given!");
                }
            } else if (!strcmp(argv[i], "-e")) {
                if (i != argc - 1) {
                    if (argv[i + 1][0] != '-') {
                        print_Object(eval_lines(scope, argv[i + 1]));
                    }
                }
            } else if (!strcmp(argv[i], "-l")) {
                if (i != argc - 1) {
                    if (argv[i + 1][0] != '-') {
                        print_Object(eval(scope, argv[i + 1]));
                    }
                }
            }
        }
    }

    Scope__destroy(scope);

    recover(true);

    return 0;
}
