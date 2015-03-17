PATH_FLAGS = -I../lib -Wl,-rpath=../lib -L../lib

all: revwords

clean:
	rm -f *.o
	rm -f revwords

revwords: revwords.c
	gcc -std=c99 $(PATH_FLAGS) revwords.c -o revwords -lhelpers