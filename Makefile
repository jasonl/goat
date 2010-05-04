CC = g++
CFLAGS = -Wall
SRC = core/*.cpp core/ast/*.cpp
TEST_SRC = test/*.cpp

debug: core/*.cpp core/ast/*.cpp core/ast/*.hpp core/*.h
	@${CC} ${CFLAGS} -ggdb ${SRC} -o goat

release: core/*.cpp core/*.h
	@${CC} ${CFLAGS} -O1 ${SRC} -o goat

goat-test: core/*.cpp core/*.h test/*.cpp test/*.gt test/*.h
	@$(CC) ${CFLAGS} -O0 -ggdb -D TEST -I ./core ${SRC} ${TEST_SRC} -o goat-test
