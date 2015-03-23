#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stddef.h>

ssize_t read_until(int fd, void *buf, size_t count, char delimiter) {
    ssize_t tread = 0;
    ssize_t bread = 0;
    if (count == 0) {
        return read(fd, buf, count);
    }
    while (tread < count) {
        bread = read(fd, buf + tread, count - tread);
        if (bread < 0) {
            return bread;
        } else if (bread == 0) {
            break;
        } else {
            for (int i = 0; i < bread; i++) {
                if (((char*) buf)[tread + i] == delimiter) {
                    return tread + bread;
                }
            }
            tread += bread;
        }
    }
    return tread;
}

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