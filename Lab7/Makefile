all: server client

server: Server.o
	g++ -o server Server.o 
	
client: Client.o
	g++ -o client Client.o


Server.o: Server.cpp 
	g++ -c Server.cpp
	
Client.o: Client.cpp
	g++ -c Client.cpp

clean:	
	rm server
	rm client
	rm Server.o
	rm Client.o
