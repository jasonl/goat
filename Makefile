CC = g++
CFLAGS = -Wall -Wextra
SRC = core/*.cc core/ast/*.cc core/i386/*.cc
TEST_SRC = test/*.cc
GTEST_ROOT = ~/Code/gtest-1.5.0
EXECUTABLE_NAME = goatc

debug: core/*.cc core/ast/*.cc core/ast/*.h core/*.h
	@${CC} ${CFLAGS} -ggdb ${SRC} -o ${EXECUTABLE_NAME}

release: core/*.cc core/*.h
	@${CC} ${CFLAGS} -O1 ${SRC} -o ${EXECUTABLE_NAME}

goat-test: core/*.cc core/ast/*.cc core/*.h test/*.cc test/*.gt
	@$(CC) ${CFLAGS} -O0 -ggdb -pthread -D GOATTEST -I ./core -I ${GTEST_ROOT}/include ${GTEST_ROOT}/make/gtest_main.a ${SRC} ${TEST_SRC} -o goat-test
