PATH_FLAGS = -I../lib -Wl,-rpath=../lib -L../lib

all: cat

clean:
	rm -f *.o
	rm -f cat

cat: cat.c
	gcc -std=c99 $(PATH_FLAGS) cat.c -o cat -lhelpers