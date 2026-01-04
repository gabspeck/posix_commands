/*
 *    echo — write arguments to standard output
 *    The echo utility writes its arguments to standard output, followed by a <newline>. If there are no arguments, only the <newline> is written.
 */

#include <stdio.h>

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        puts(argv[i]);
    }
    putchar('\n');
    return 0;
}
