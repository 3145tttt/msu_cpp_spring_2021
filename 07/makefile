CC=g++
FLAGS=-std=c++17 -Wall -Wextra

all: main.o
	$(CC) $(FLAGS) main.o -o main
	
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c

test: main.o
	$(CC) $(FLAGS) main.o -o main
	./main

clean:
	rm -f *.o main