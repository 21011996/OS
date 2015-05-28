all:
	LD_LIBRARY_PATH="../lib"
	gcc -std=c99 filter.c -L../lib/ -Wl,-rpath=../lib -lhelpers -o filter

clean:
	rm filter