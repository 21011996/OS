#include "helpers.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

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

int spawn(const char * file, char * const argv []) {
    pid_t pid = fork();
    int status;
    if (pid == 0) {
        execvp(file, argv);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            return -1;
        }
    }
    return -1;
}

struct execargs_t new_args(int argc, char** argv)
{
    struct execargs_t result;
    result.argv = (char**) malloc((argc + 1) * sizeof(char*));
    int i;
    for (i = 0; i < argc; i++) 
        result.argv[i] = strdup(argv[i]); 
    result.argv[argc] = NULL;
    return result;
}

int exec(struct execargs_t * given) {
	if (spawn(args->argv[0], args->argv) == -1)
        return -1;
    return 0;
}

int childcount;
int* childarray;

void killer(int sig) {
	for (int i = 0; i < childcount; i++) 
        kill(childarray[i], SIGKILL);
    childcount = 0;
}

int runpiped(struct execargs_t ** programs, size_t n) {
	if (n == 0)
        return 0;
	
    int pipefd[n-1][2];
	int pidarray[n];
	
	for (int i=0; i< n-1;i++) 
        if (pipe2(pipefd[i],O_CLOEXEC)<0)
            return -1;
		
	for (int i=0;i<n;i++) {
		if (!(pidarray[i]=fork())) {
            if (i!=0)
				dup2(pipefd[i-1][0], STDIN_FILENO);
			if (i!=n-1)
				dup2(pipefd[i][1], STDOUT_FILENO);
			_exit(execvp(programs[i]->argv[0], programs[i]->argv));	
		}
        if (pidarray[i]==-1)
            return -1;
	}
	
	for (int i = 0; i < n - 1; i++) {
		close(pipefd[i][0]);
		close(pipefd[i][1]);
	}
    
    childcount=n;
    childarray=(int*) pidarray;
	
    struct sigaction action;				//some one told that this is very bad(
    memset(&action, '\0', sizeof(action));
    action.sa_handler = &killer;
   
    if (sigaction(SIGINT, &action, NULL) < 0) 
        return -1;

	int status;
	for (int i = 0; i < n; i++) 
        waitpid(pidarray[i], &status, 0);
    childcount = 0;
    return 0;
}