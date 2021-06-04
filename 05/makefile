CC=g++
FLAGS=-std=c++17 -Wall -Wextra

all: main.o
	$(CC) $(FLAGS) main.o -o main
	
main.o:
	$(CC) $(FLAGS) main.cpp -c

test: main.o
	g++ -std=c++17 main.o -o test
	./test

clean:
	rm -f *.o main test