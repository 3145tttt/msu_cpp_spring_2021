CC=g++
FLAGS=-std=c++11 -Wall -Wextra -Wreorder

all: main.o
	$(CC) $(FLAGS) main.o -lpthread -o main
	
main.o:
	$(CC) $(FLAGS) main.cpp -c


test:
	./main

clean:
	rm -f *.o main