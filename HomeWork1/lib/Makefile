CFLAGS = -Wall -Werror -std=c99

all: libhelpers.so

clean:
	rm -f *.o
	rm -f *.so

libhelpers.so: helpers.o
	gcc -shared -o libhelpers.so helpers.o

helpers.o: helpers.c
	gcc $(CFLAGS) -c helpers.c