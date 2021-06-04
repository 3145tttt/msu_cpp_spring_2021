CC=g++
FLAGS=-std=c++17 -Wall -Wextra

all: main.o bigint.o
	$(CC) $(FLAGS) main.o bigint.o -o main
	
main.o:
	$(CC) $(FLAGS) main.cpp -c

bigint.o:
	$(CC) $(FLAGS) bigint.cpp -c

test: main.o bigint.o
	g++ -std=c++17 main.o bigint.o -o test
	./test

clean:
	rm -f *.o main test