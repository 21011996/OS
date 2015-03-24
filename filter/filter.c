#include <helpers.h>
#include <stdlib.h>
#include <string.h>

char line[4097];
size_t line_pos = 0;

char ** argvs;

int main(int argc, char ** argv) {
    char buf[4096];
    size_t nread;

    if (argc < 2) {
		write(STDERR_FILENO, "incorrect args\n", strlen("incorrect args\n"));
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
        nread = read_until(STDIN_FILENO, buf, sizeof(buf), '\n');

        for (int i = 0; i < nread; i++) {
            if (buf[i] == '\n') {
                if (line_pos != 0) {
                    line[line_pos] = 0;
                    if (spawn(argvs[0], argvs) == 0) {
						write(STDOUT_FILENO, line, strlen(str));
						write(STDOUT_FILENO, '\n', 1);
					}
                }
                line_pos = 0;
            } else {
                line[line_pos++] = buf[i];
            }
        }

    } while (nread > 0);

    if (line_pos != 0) {
        line[line_pos] = 0;
        if (spawn(argvs[0], argvs) == 0) {
			write(STDOUT_FILENO, line, strlen(str));
			write(STDOUT_FILENO, '\n', 1);
		}
    }
    free(argvs);
    return 0;
}