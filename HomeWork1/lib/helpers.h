#ifndef _HELPERS_
#define _HELPERS_

#include <unistd.h>
#include <stddef.h>

ssize_t read_(int fd, void *buf, size_t counter);
ssize_t write_(int fd, const void *buf, size_t counter);

#endif