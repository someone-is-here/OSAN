all: source

source: source.o
	g++ -o source source.o

source.o: source.cpp func.cpp func.h
	g++ -c source.cpp

clean:
	rm source *.o
