CC=g++
FLAGS=-std=c++11 -Wall -Wextra -Wreorder

all: main.o
	$(CC) $(FLAGS) main.o -o main
	
main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -c

test:
	./main

clean:
	rm -f *.o main