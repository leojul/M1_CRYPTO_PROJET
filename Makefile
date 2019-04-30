CC=gcc
CFLAGS= -std=c99 -Wall -Werror

all: main

main: main.o cbc.o tczero.o birthday_attack.o
	$(CC) -o main main.o cbc.o tczero.o birthday_attack.o $(CFLAGS)

main.o: main.c cbc.h tczero.h
	$(CC) -o main.o -c main.c $(CFLAGS)

birthday_attack.o: birthday_attack.c cbc.h tczero.h
	$(CC) -o birthday_attack.o -c birthday_attack.c $(CFLAGS)

cbc.o: cbc.c tczero.h
	$(CC) -o cbc.o -c cbc.c $(CFLAGS)

tczero.o: tczero.c tczero.h
	$(CC) -o tczero.o -c tczero.c $(CFLAGS)

clean:
	rm -rf *.o