#include "helpers.h"
#include "errno.h"

ssize_t read_(int fd, void *buf, size_t counter) {
    ssize_t tread = 0;
    ssize_t bread = 0;
    while (tread < counter) {
        bread = read(fd, buf + tread, counter - tread);
        if (bread <= 0) {
            break;
        } else {
            tread += bread;
        }
    }
    if (bread < 0) {
        return -1;
    }
        return tread;
}

ssize_t write_(int fd, const void *buf, size_t counter) {
    ssize_t twritten = 0;
    ssize_t bwritten = 0;
    while (twritten < counter) {
        bwritten = write(fd, buf + twritten, counter - twritten);
        if (bwritten <= 0) {
            return bwritten;
        } else {
            twritten += bwritten;
        }
    }
    if (bwritten < 0) {
        return -1;
    }
    return twritten;
}