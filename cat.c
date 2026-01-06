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
        unsigned char buf[BUFSIZ];
        while (true) {
            const size_t len = fread(buf, 1, sizeof buf, f);
            if (len > 0) {
                if (fwrite(buf, 1, len, stdout) != len) {
                    perror("stdout");
                    break;
                }
            }
            if (len < sizeof buf) {
                if (ferror(f)) {
                    perror(filename);
                }
                break;
            }
        }
        if (fclose(f) != 0) {
            fprintf(stderr, "error closing %s: %s\n", filename, strerror(errno));
        };
    }


    return 0;
}
