all: libhelpers tester

clean:
	rm -f *.o
	rm -f *.so
	rm -f *.out
	rm -f tester

libhelpers: libhelpers.so

libhelpers.so: helpers.o
	gcc -shared -o libhelpers.so helpers.o
	
helpers.o: helpers.c 
	gcc -c -std=c99 -fPIC -Wall -Werror helpers.c -o helpers.o 