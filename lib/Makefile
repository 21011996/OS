all:
	gcc -shared -g -o libhelpers.so -std=c99 -fPIC helpers.c
	c99 -fPIC -Wall -shared bufio.c -o libbufio.so