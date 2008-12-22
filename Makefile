crypter: crypter.o
	gcc -o crypter crypter.o -L/usr/lib64 -lgcrypt -lgpg-error

crypter.o: crypter.c
	gcc -Wall -I/usr/include -c crypter.c

clean:
	rm -f *.o 
	rm -f *~

