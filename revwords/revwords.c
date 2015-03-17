#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "helpers.h"

#define BUF_SIZE 4096

size_t wlength = 0;
const char WORDS_DELIMITER = ' ';

char buffer[4096];
char word[4096];

void reverse() {
    for (int j = 0; j < wlength / 2; j++) {
        char temp = word[j];
        word[j] = word[wlength - j - 1];
        word[wlength - j - 1] = temp;
    }
    write_(STDOUT_FILENO, word, wlength);
}

int main() {
    while (1) {
        ssize_t bread = read_until(STDIN_FILENO, buffer, BUF_SIZE, WORDS_DELIMITER);
        if (bread < 0) {
            fprintf(stderr, "%s\n", strerror(errno));            
            return 1;
        }

        for (int i = 0; i < bread; i++) {
            if (buffer[i] == WORDS_DELIMITER) {
                if (wlength > 0) {
                    reverse();
                }
                wlength = 0;
                write_(STDOUT_FILENO, &WORDS_DELIMITER, 1);
            } else {
                word[wlength++] = buffer[i];
            }
        }
    }
    
    if (wlength > 0) {
        reverse();
    }

    return 0;
}