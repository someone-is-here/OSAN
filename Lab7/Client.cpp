// Client side C/C++ program to demonstrate Socket
// programming

#include <pthread.h>
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

void* write_to_server(void* client_fd){
	
	string str;
    	while(true){
    		cout<<"ENTER MESSAGE TO SERVER:"<<endl;
    		getline (cin, str);
    		
    		if(str=="EXIT"){
    		  break;
    		}
   
    		size_t res = send((long)client_fd, str.c_str(), strlen(str.c_str()), 0);
    		if (res > 0){
    			cout << "Sent successfully!" << endl;
    		}else if (res==0){
      			break;
      		}	
    	}
    	
}
void* read_from_server(void* client_fd){

	char buffer[1024] = { 0 };

	while (true) {
    		size_t res = recv((long)client_fd, buffer, 1024, 0);
    		if(res > 0){
      			cout << "Recieved from server: " << buffer << endl;
      			memset(&buffer[0], 0, sizeof(buffer));
      		}else if (res==0){
      		break;
      		}
    	}
}

int main(int argc, char const* argv[]){

	int status, valread, client_fd;
	struct sockaddr_in serv_addr;

	if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((status
		= connect(client_fd, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	 
	pthread_t ptid, ptid2;
  
    	// Creating a new thread
    	pthread_create(&ptid, NULL, &write_to_server, (void*)client_fd);
    	pthread_create(&ptid2, NULL, &read_from_server, (void*)client_fd);
    		
	pthread_join(ptid, NULL);
    	pthread_join(ptid2, NULL);
	
    	
	//pthread_exit(NULL);
	
	// closing the connected socket
	close(client_fd);
	return 0;
}

