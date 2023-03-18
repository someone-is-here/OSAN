all: source

source: Source.o
	g++ -o source Source.o

Source.o: Source.cpp 
	g++ -c Source.cpp

clean:
	rm source *.o
