#include "../lib/helpers.h"
#include <stdlib.h>
#include <string.h>

char line[4096];
size_t pos = 0;
char ** argvs;

void println(int fd, const char * str) {
    write_(fd, str, strlen(str));
    char c = '\n';
    write_(fd, &c, 1);
}
 
int main(int argc, char ** argv) {
    char buffer[4096];
    size_t bread;

    if (argc < 2) {
        println(STDERR_FILENO, "No args were given");
        return 1;
    } else {
        argvs = malloc(sizeof(char *) * (argc + 1));
        for (int i = 0; i < argc - 1; i++) {
            argvs[i] = argv[i + 1];
        }
        argvs[argc - 1] = line;
        argvs[argc] = NULL;
    }
 
    do {
        bread = read_until(STDIN_FILENO, buffer, sizeof(buffer), '\n');
        for (int i = 0; i < bread; i++) {
            if (buffer[i] == '\n') {
                if (pos != 0) {
                    line[pos] = 0;
                    if (spawn(argvs[0], argvs) == 0) {
                        println(STDOUT_FILENO, line);
                    }
                }
                pos = 0;
            } else {
                line[pos++] = buffer[i];
            }
        }
    } while (bread > 0);
 
    if (pos != 0) {
        line[pos] = 0;
        if (spawn(argvs[0], argvs) == 0) {
            println(STDOUT_FILENO, line);
        }
    }
    free(argvs);
    return 0;
}