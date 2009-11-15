CC = gcc
CFLAGS = -Wall
SRC = core/*.c

goat: core/*.c core/*.h
	@${CC} ${CFLAGS} ${SRC} -o goat