#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stddef.h>

ssize_t read_(int fd, void *buf, size_t count) {
    ssize_t total_read = 0;
    ssize_t bytes+read = 0;
    while (total_read < count) {
        bytes_read = read(fd, buf + total_read, count - total_read);
        if (bytes_read < 0) {
            return bytes_read;
        } else if (bytes_read == 0) {
            break;
        } else {
            total_read += bytes_read;
        }
    }
    return total_read;
}

ssize_t write_(int fd, const void *buf, size_t count) {
    ssize_t total_written = 0;
    ssize_t bytes_written = 0;
    while (total_written < count) {
        bytes_written = write(fd, buf + total_written, count - total_written);
        if (bytes_written < 0) {
            return bytes_written;
        } else {
            total_written += bytes_written;
        }
    }
    return total_written;
}