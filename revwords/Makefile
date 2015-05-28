all:
	LD_LIBRARY_PATH="../lib"
	gcc -std=c99 revwords.c -L../lib/ -Wl,-rpath=../lib -lhelpers -o revwords

clean:
	rm revwords