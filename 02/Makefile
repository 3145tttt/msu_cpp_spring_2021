CC=g++
FLAGS=-std=c++17 -Wall -Wextra

all: main.o tokenParser.o
	$(CC) $(FLAGS) main.o tokenParser.o -o main
	
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c

tokenParser.o: tokenParser.hpp tokenParser.cpp
	$(CC) $(FLAGS) tokenParser.cpp -c

test: main.o tokenParser.o
	g++ -std=c++17 main.o tokenParser.o -o test
	./test

clean:
	rm -f *.o main

