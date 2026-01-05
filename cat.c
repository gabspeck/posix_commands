/*
 *    cat — concatenate and print files
 *    The cat utility shall read files in sequence and shall write their contents to the standard output in the same sequence.
*/

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    bool unbuffered = false;

    int argi = 1;
    for (argi = 1; argi < argc && argv[argi][0] == '-'; argi++) {
        for (int j = 1; argv[argi][j] != '\0'; j++) {
            if (argv[argi][j] == 'u') {
                unbuffered = true;
            }
        }
    }

    for (; argi < argc; argi++) {
        char *filename = argv[argi];
        FILE *f = fopen(filename, "r");
        if (f == NULL) {
            perror(filename);
            continue;
        }
        char buf[512];
        while (!feof(f)) {
            const size_t len = fread(buf, 1, 50, f);
            if (ferror(f)) {
                perror(filename);
                break;
            }
            fwrite(buf, 1, len, stdout);
        }
        if (fclose(f)) {
            fprintf(stderr, "error closing %s: %s\n", filename, strerror(errno));
        };
    }


    return 0;
}
