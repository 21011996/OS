#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	char buf[4096];
    char** argvs = (char**)malloc(sizeof(char*) * (argc + 2));
    int i;
    for (i = 0; i < argc - 1; i++)
    {
        argvs[i] = argv[i + 1];
    }
    argvs[argc] = NULL;
    while (1)
    {
        ssize_t read = read_until(STDIN_FILENO, buf, 4096, '\n');
        if (read == 0)
        {
            return 0;
        }
        else if (read == -1)
        {
            perror("Error occured while we were reading");
            return 1;
        }
        if (buf[read - 1] == '\n') {
            buf[read -1] = 0;
        }
        argvs[argc - 1] = buf;
        int res = spawn(argvs[0], argvs);
        if (res == 0)
        {
            if (buf[read - 1] == 0) {
                buf[read - 1] = '\n';
            }
            write_(STDOUT_FILENO, buf, read);
        }
    }
    free(argvs);
    return 0;
}