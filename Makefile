CC = gcc
CFLAGS = -Wall
SRC = core/*.c
TEST_SRC = test/*.c

goat: core/*.c core/*.h
	@${CC} ${CFLAGS} ${SRC} -o goat

goat-test: core/*.c core/*.h test/*.c test/*.gt test/*.h
	@$(CC) ${CFLAGS} -D TEST -I ./core ${SRC} ${TEST_SRC} -o goat-test
	@./goat-test