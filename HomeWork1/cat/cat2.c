#include <stdio.h>
#include "../lib/helpers.h"

#define BUF_SIZE 1024

int main(int argc, char * argv[]) {

    char buf[BUF_SIZE];
    while (1) {
        ssize_t bytes_read = read_(STDIN_FILENO, buf, BUF_SIZE);
        if (bytes_read < 0) {
            break;
        }
        write_(STDOUT_FILENO, buf, bytes_read);
        if (bytes_read == 0) {
            break;
        }
    }

}