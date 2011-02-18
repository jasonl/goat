CC = g++
CFLAGS = -Wall -Wextra
SRC = core/*.cpp core/ast/*.cpp core/i386/*.cpp
TEST_SRC = test/*.cpp
GTEST_ROOT = ~/Code/gtest-1.5.0
EXECUTABLE_NAME = goatc

debug: core/*.cpp core/ast/*.cpp core/ast/*.hpp core/*.h
	@${CC} ${CFLAGS} -ggdb ${SRC} -o ${EXECUTABLE_NAME}

release: core/*.cpp core/*.h
	@${CC} ${CFLAGS} -O1 ${SRC} -o ${EXECUTABLE_NAME}

goat-test: core/*.cpp core/ast/*.cpp core/*.h test/*.cpp test/*.gt
	@$(CC) ${CFLAGS} -O0 -ggdb -pthread -D GOATTEST -I ./core -I ${GTEST_ROOT}/include ${GTEST_ROOT}/make/gtest_main.a ${SRC} ${TEST_SRC} -o goat-test 
