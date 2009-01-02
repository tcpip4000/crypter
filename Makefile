 
# Copyright (C) 2008 ER Technology
# Juan P Daza P

# TODO: migrate this file to a more generic form or maybe use automake

CC=gcc
CFLAGS=-Wall -std=c99 -O2

modalgen: modalgen.o libcrypter.a modaler
	$(CC) tests/modalgen.o -L./src -L/usr/lib -lgcrypt -lgpg-error -lcrypter -o tests/modalgen

modaler: modaler.o libcrypter.a
	$(CC) tests/modaler.o -L./src -L/usr/lib -lgcrypt -lgpg-error -lcrypter -o tests/modaler

libcrypter.a: crypter.o
	ar cr src/libcrypter.a src/crypter.o

modalgen.o: tests/modalgen.c
	$(CC) $(CFLAGS) -I/usr/include -I./src -c tests/modalgen.c -o tests/modalgen.o

modaler.o: tests/modaler.c
	$(CC) $(CFLAGS) -I/usr/include -I./src -c tests/modaler.c -o tests/modaler.o

crypter.o: src/crypter.c
	$(CC) $(CFLAGS) -I/usr/include -I./src -c src/crypter.c -o src/crypter.o

clean:
	rm -f *.o 
	rm -f *~ 
	rm -f src/*.[oa]
	rm -f src/*~
	rm tests/modaler
	rm tests/modalgen

