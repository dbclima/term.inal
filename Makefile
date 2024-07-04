CC = gcc
CFLAGS = -Wall -Werror -Iinclude

OUTPUT = bin/main

all: dirs $(OUTPUT)

$(OUTPUT): build/main.o build/palavra.o build/interface.o
	$(CC) build/main.o build/palavra.o build/interface.o -o $(OUTPUT)

build/main.o: src/main.c include/palavra.h
	$(CC) -c src/main.c -o build/main.o $(CFLAGS)

build/palavra.o: src/palavra.c include/palavra.h
	$(CC) -c src/palavra.c -o build/palavra.o $(CFLAGS)

build/interface.o: src/interface.c include/interface.h
	$(CC) -c src/interface.c -o build/interface.o $(CFLAGS)

dirs:
	rd /s /q bin build
	mkdir bin build

clean:
	rm -f bin/* build/*.o
