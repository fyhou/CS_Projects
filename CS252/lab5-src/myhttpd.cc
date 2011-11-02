
const char * usage =
" \n"
"daytime-server:\n"
" \n"
"Simple server program that shows how to use socket calls \n"
"in the server side.\n"
" \n"
"To use it in one window type:\n"
" \n"
" daytime-server <port> \n"
" \n"
"Where 1024 < port < 65536. \n"
" \n"
"In another window type: \n"
" \n"
" telnet <host> <port>\n"
" \n"
"where <host> is the name of the machine where daytime-server\n"
"is running. <port> is the port number you used when you run \n"
"daytime-server. \n"
" \n"
"Then type your name and return. You will get a greeting and \n"
"the time of the day.\n"
" \n";


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

int QueueLength = 5;

// Processes time request
void processRequest(int socket);

int
main(int argc, char ** argv)
{
	// Print usage if not enough arguments
	if (argc < 2) {
		fprintf(stderr, "%s", usage);
		exit(-1);
	 }
	
	// Get the port from the arguments
	int port = atoi(argv[1]);
	
	// Set the IP address and port for this server
	struct sockaddr_in serverIPAddress; 
	memset(&serverIPAddress, 0, sizeof(serverIPAddress));
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);
	
	// Allocate a socket
	int masterSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (masterSocket < 0) {
		perror("socket");
		exit(-1);
	}

	// Set socket options to reuse port. Otherwise we will
	// have to wait about 2 minutes before reusing the same port number
	int optval = 1; 
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR,(char *) &optval, sizeof(int));
	 
	// Bind the socket to the IP address and port
	int error = bind(masterSocket,
			 (struct sockaddr *)&serverIPAddress,
			sizeof(serverIPAddress));
	if (error) {
		perror("bind");
		exit(-1);
	}
	
	// Put socket in listening mode and set the 
	// size of the queue of unprocessed connections
	error = listen(masterSocket, QueueLength);
	if (error) {
		perror("listen");
		exit(-1);
	}

	// wait 
	while (1) {
		// Accept incoming connections
		struct sockaddr_in clientIPAddress;
		int alen = sizeof(clientIPAddress);
		int slaveSocket = accept(masterSocket,
					 (struct sockaddr *)&clientIPAddress,
					 (socklen_t*)&alen);

		if (slaveSocket < 0) {
			perror("accept");
			exit(-1);
		}

		// Process request.
		processRequest(slaveSocket);

		// Close socket
		close(slaveSocket);
	}	
}

void
processRequest(int socket)
{
	int n;
	int gotGet = 0;
	char newChar, oldChar;

	int gotDP = 0;
	char docPath[1024];
	
	int length = 0;
	char currString[1024];
	
	while (n = read(socket, &newChar, sizeof(newChar))) {			
		if (newChar == ' ') {
			if (gotGet == 0) {
				gotGet = 1;
			}
			else if (gotDP == 0) {
				length++;
				currString[length-1] = '\0';
				strcpy(docPath, currString);
			}
		}
		else if (oldChar == '\n' && newChar == '\r') {
			break;
		}
		else {
			oldChar = newChar;
			if (gotGet == 1) {
				length++;
				currString[length-1] = newChar;
			}		
		}	
	}

	printf("docPath is: %s\n", &docPath);
	



	/*
	FILE * document;
	document = fopen(cwd, "r");

	if (document == 0) {
		const char *notFound = "File not found";
		write(socket, "HTTP/1.0", strlen("HTTP/1.0"));
		write(socket, " ", 1);
		write(socket, "404", 3);
		write(socket, "File", 4);
		write(socket, " ", 1);
		write(socket, "Not", 3);
		write(socket, " ", 1);
		write(socket, "Found", 5);
		write(socket, "\n\r", 2);
		write(socket, "Server:", 7);
		write(socket, "Wolf Gang", 9);
		write(socket, "\n\r", 2);
		write(socket, "Content-type:", 13);
		write(socket, " ", 1);
		write(socket, "text/plain", 10);
		write(socket, "\n\r", 2);
		write(socket, "\n\r", 2);
		write(socket, notFound, strlen(notFound));
	}*/
}
