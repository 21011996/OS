#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "helpers.h"

#define BUF_SIZE 4096

size_t wlength = 0;
const char WORDS_DELIMITER = ' ';

char buffer[4096];

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

void writelength(ssize_t wlength) {
    char length[4096];
    int a = sprintf(length, "%zu", wlength);
    write_(STDOUT_FILENO, length, a);
}

int main() {
    ssize_t bread;
    do
    {
    bread = (size_t) read_until(STDIN_FILENO, buffer, BUF_SIZE, ' ');
        if (bread == -1) {
            fprintf(stderr, "%s\n",strerror(errno));
            return 1;
        }

        for (int i = 0; i < bread; i++) {
            if (buffer[i] == ' ') {
                writelength(wlength);
                wlength = 0;
                write_(STDOUT_FILENO, &WORDS_DELIMITER, 1);
            } else {
                wlength++;
            }
        }
    } while (bread > 0);
    
    if (wlength != 0) {
        writelength(wlength);
    }

    return 0;
}