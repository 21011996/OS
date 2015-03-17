
all: lib/libhelpers.so cat/cat revwords/revwords

lib/libhelpers.so: 
	cd lib && make

cat/cat revwords/revwords:
	cd revwords && make	
	cd cat && make

clean:
	cd cat && make clean
	cd revwords && make clean
	cd lib && make clean

