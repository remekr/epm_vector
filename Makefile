all: vector

vector: main.o vector.o
	g++ main.o vector.o -o bin/vector

main.o: src/main.cpp
	g++ -c src/main.cpp

vector.o: src/vector.cpp
	g++ -c src/vector.cpp


run:
	./bin/vector
	
clean:
	rm *o bin/*