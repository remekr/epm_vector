CC=g++
CFLAGS=-c -std=c++11 -Wall -Werror

all: vector tests memory format

run: vector

vector: main.o vector.o
	$(CC) main.o vector.o -o bin/vector

main.o: src/main.cpp
	$(CC) $(CFLAGS) src/main.cpp

vector.o: src/vector.cpp
	$(CC) $(CFLAGS) src/vector.cpp


tests: fixture vector.o

fixture: vector_ut.o
	./bin/tests

vector_ut.o: src/ut/vector.cpp
	$(CC) -std=c++11 -I/media/sf_Bench/googletest-release-1.7.0/include -pthread src/ut/vector.cpp /media/sf_Bench/googletest-release-1.7.0/make/gtest_main.a vector.o -o bin/tests

memory: vector
	valgrind --tool=memcheck bin/tests

run:
	./bin/vector

format:
	ls src/*.cpp src/*.h src/ut/*.cpp | xargs clang-format-3.5 -i -style=file

clean:
	rm *o bin/*
