CC = gcc
CFLAGS = -Wall
SRC = *.c

goat: *.c
	@${CC} ${CFLAGS} ${SRC} -o goat