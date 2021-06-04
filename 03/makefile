CC=g++
FLAGS=-std=c++17 -Wall -Wextra

all: main.o matrix.o
	$(CC) $(FLAGS) main.o matrix.o -o main
	
main.o:
	$(CC) $(FLAGS) main.cpp -c

matrix.o:
	$(CC) $(FLAGS) matrix.cpp -c

test: main.o matrix.o
	g++ -std=c++17 main.o matrix.o -o test
	./test

clean:
	rm -f *.o main test

