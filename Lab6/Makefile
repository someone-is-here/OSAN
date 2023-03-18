all: source

source: Threads.o
	g++ -o source Threads.o

Threads.o: Threads.cpp 
	g++ -c Threads.cpp

clean:
	rm source *.o
