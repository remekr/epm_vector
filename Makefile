CC=g++
CFLAGS=-c -Wall -Werror

all: vector run tests memory

run: vector

vector: main.o vector.o
	$(CC) main.o vector.o -o bin/vector

main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp

vector.o: src/vector.cpp
	$(CC) $(CFLAGS) src/vector.cpp


tests: fixture

fixture: vector_ut.o
	./bin/tests

vector_ut.o: src/ut/vector.cpp
	$(CC) -I/media/sf_Bench/googletest-release-1.7.0/include -pthread src/ut/vector.cpp /media/sf_Bench/googletest-release-1.7.0/make/gtest_main.a -o bin/tests

memory: vector fixture
	valgrind --tool=memcheck bin/tests
	
run:
	./bin/vector
	
clean:
	rm *o bin/*
