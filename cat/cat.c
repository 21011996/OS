#include <stdio.h>
#include <unistd.h>
#include "../lib/helpers.h"

int main(int argc, char * argv[]) {

    char buffer[1024];
    while (1) {
        ssize_t bread = read_(STDIN_FILENO, buffer, 1024);
        if (bread < 0) {
            break;
        }
        write_(STDOUT_FILENO, buffer, bread);
        if (bread == 0) {
            break;
        }
    }
}