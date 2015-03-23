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

void reverse() {
    for (int i = 0; i < wlength / 2; i++) {
        char temp = word[i];
        word[i] = word[wlength - i - 1];
        word[wlength - i - 1] = temp;
    }
    char length[4096];
    itoa(wlength,length);
    int a = wlength;
    int b;
    do{
    	a*=10;
    	b++;
    } while (a>0);
    write_(STDOUT_FILENO, length, b);
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
                if (wlength != 0) {
                    reverse();
                }
                wlength = 0;
                write_(STDOUT_FILENO, &WORDS_DELIMITER, 1);
            } else {
                word[wlength++] = buffer[i];
            }
        }
    } while (bread > 0);
    
    if (wlength != 0) {
        reverse();
    }

    return 0;
}