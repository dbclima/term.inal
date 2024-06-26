CC = gcc
CFLAGS = -Wall -Werror -Iinclude

OUTPUT = bin/main

all: main palavra
	$(CC) build/main.o build/palavra.o -o $(OUTPUT)

main:
	$(CC) -c src/main.c -o build/main.o $(CFLAGS)

palavra:
	$(CC) -c src/palavra.c -o build/palavra.o $(CFLAGS)

clean:
	rm -f bin/* build/*.o