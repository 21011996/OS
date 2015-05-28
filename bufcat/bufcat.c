#include "../lib/bufio.h"

int main() {
    int returncode = 0;
    struct buf_t * buf = buf_new(4096);
    ssize_t bread, bwritten;

    do {
        bread = buf_fill(STDIN_FILENO, buf, buf_capacity(buf));
        bwritten = buf_flush(STDOUT_FILENO, buf, buf_size(buf));
        if (bread == -1 || bwritten == -1) {
            returncode = 1;
            break;
        }
    } while (bread > 0);

    buf_free(buf);
    return returncode;
}