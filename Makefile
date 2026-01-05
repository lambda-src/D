CC=gcc
LIBS=
OUT=D

main: ./src/main.c
	mkdir -p ./build
	$(CC) ./src/*.c -o ./build/$(OUT) $(LIBS)
