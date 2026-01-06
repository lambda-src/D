CC=gcc
LIBS=-lncurses
OUT=D

main: ./src/main.c
	mkdir -p ./build
	$(CC) ./src/*.c $(LIBS) -o ./build/$(OUT) $(LIBS)
