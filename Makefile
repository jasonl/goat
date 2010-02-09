CC = g++
CFLAGS = -Wall
SRC = core/*.cpp
TEST_SRC = test/*.cpp

debug: core/*.cpp core/*.h
	@${CC} ${CFLAGS} -ggdb ${SRC} -o goat

release: core/*.cpp core/*.h
	@${CC} ${CFLAGS} -O1 ${SRC} -o goat

goat-test: core/*.cpp core/*.h test/*.c test/*.gt test/*.h
	@$(CC) ${CFLAGS} -O0 -ggdb -D TEST -I ./core ${SRC} ${TEST_SRC} -o goat-test
