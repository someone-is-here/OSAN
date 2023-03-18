// Server side C/C++ program to demonstrate Socket
// programming

#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define PORT 8080

using namespace std;

//using namespace std;
void* write_to_client(void* server_fd){

	int val_read;
	string str;
	
    	while(true){
    	
    		getline (cin, str);
    	
    		if(str=="EXIT"){
    		  break;
    		}
   
    		size_t res = send((long)server_fd, str.c_str(), strlen(str.c_str()), 0);
		if(res > 0){
			printf("Message sent to client\n");
		}else if (res==0){
			break;
		}
		
	}
}

void* read_from_client(void* new_socket){
	char buffer[1024] = { 0 };
	
	while(true){
		size_t res = read((long)new_socket, buffer, 1024);
		if(res>0){
			cout << "READ FROM CLIENT: " << buffer << endl;
			memset(&buffer[0], 0, sizeof(buffer));
			//printf("MESSAGE FROM CLIENT %s\n", buffer);	
		}else if (res==0){
			break;
		}
	}
}


int main(int argc, char const* argv[]) {

	int server_fd, new_socket, valread;
	
	struct sockaddr_in address;
	
	int opt = 1;
	int addrlen = sizeof(address);
	

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				SO_REUSEADDR | SO_REUSEPORT, &opt,
				sizeof(opt))) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr*)&address,
			sizeof(address))
		< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket
		= accept(server_fd, (struct sockaddr*)&address,
				(socklen_t*)&addrlen))
		< 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}
	
	pthread_t ptid, ptid1;
  
    	// Creating a new thread
    	pthread_create(&ptid, NULL, &write_to_client, (void*)new_socket);
    	
    	pthread_create(&ptid1, NULL, &read_from_client, (void*)new_socket);
    
    	pthread_join(ptid, NULL);
    	pthread_join(ptid1, NULL);
	
	pthread_exit(NULL);
	
	// closing the connected socket
	close(new_socket);
	
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}

