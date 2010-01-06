CC = /home/jason/llvm/Debug/bin/clang
CFLAGS = -Wall -x c
SRC = core/*.c
TEST_SRC = test/*.c

debug: core/*.c core/*.h
	@${CC} ${CFLAGS} -ggdb ${SRC} -o goat

release: core/*.c core/*.h
	@${CC} ${CFLAGS} -O1 ${SRC} -o goat

goat-test: core/*.c core/*.h test/*.c test/*.gt test/*.h
	@$(CC) ${CFLAGS} -O0 -ggdb -D TEST -I ./core ${SRC} ${TEST_SRC} -o goat-test
