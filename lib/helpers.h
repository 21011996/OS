#ifndef _HELPERS_
#define _HELPERS_

#include <unistd.h>

struct execargs_t {
	char * prog;
	char * args[100];
	int args_cnt;
}

extern int exec(struct execargs_t * args);
extern int runpiped(struct execargs_t ** programs, size_t n);
extern int spawn(const char * file, char * const argv[]);
extern ssize_t read_(int fd, void *buf, size_t count);
extern ssize_t read_until(int fd, void *buf, size_t count, char delimiter);
extern ssize_t write_(int fd, const void *buf, size_t count);
extern int spawn(const char* file, char* const argv[]);

#endif