
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
#include <signal.h>

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

pthread_mutex_t mutex; // the lock

int QueueLength = 5;

// Processes time request
void processRequest(int socket);
void processRequestThread(int socket);
void poolSlave(int socket);

// function to handle killzombie
extern "C" void killzombie( int sig ) {
	while(waitpid(-1,NULL,WNOHANG) > 0);
}

int
main(int argc, char ** argv)
{
	// to handle killzombie;
	struct sigaction signalAction;
	signalAction.sa_handler = killzombie;
	sigemptyset(&signalAction.sa_mask);
	signalAction.sa_flags=SA_RESTART;
	int ezz = sigaction(SIGCHLD,&signalAction,NULL);
	if (ezz) { 
		perror("sigaction");
		exit(-1);
	}

	int port;
	int mode = 0; // 0 single, 1 process, 2 threads, 3 threadpool
	// Print usage if not enough arguments
	/* if (argc < 2) {
		fprintf(stderr, "%s", usage);
		exit(-1);
	 }
	*/

	if (argc == 1) {
		port = 1200;		
	}
	else if (argc == 2) {
		port = atoi(argv[1]); 
	}
	else if (argc == 3) {
		// get port
		port = atoi(argv[2]);

		// determine mode
		if (strcmp(argv[1], "-f") == 0) {
			mode = 1;
			//printf("mode is 1\n");
		}
		else if (strcmp(argv[1], "-t") == 0) {
			mode = 2;
			//printf("mode is 2\n");
		}
		else if (strcmp(argv[1], "-p") == 0) {
			mode = 3;		
			//printf("mode is 3\n");
		}
		else {
			fprintf(stderr, "%s", usage);
			exit(-1);
		}
	}
	else {
		fprintf(stderr, "%s", usage);
		exit(-1);
	}

	if (port < 1024 && port > 65536) {
		fprintf(stderr, "%s", usage);
		exit(-1);
	}
	
	// Get the port from the arguments
	// int port = atoi(argv[1]);
	
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


	if (mode == 3) {
		// thread attributes initialization 
		pthread_t t1, t2, t3, t4, t5;
		pthread_attr_t attr;

		pthread_attr_init( &attr );
		pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

		// initalize the lock
		pthread_mutex_init(&mutex, NULL);
	
		pthread_create(&t1, &attr, (void *(*)(void *)) poolSlave, (void *) masterSocket);
		pthread_create(&t2, &attr, (void *(*)(void *)) poolSlave, (void *) masterSocket);
		pthread_create(&t3, &attr, (void *(*)(void *)) poolSlave, (void *) masterSocket);
		pthread_create(&t4, &attr, (void *(*)(void *)) poolSlave, (void *) masterSocket);
		pthread_create(&t5, &attr, (void *(*)(void *)) poolSlave, (void *) masterSocket);

		pthread_join(t1, NULL);
	}

	else {
	// wait 
		while (1) {
			// Accept incoming connections
			struct sockaddr_in clientIPAddress;
			int alen = sizeof(clientIPAddress);
			int slaveSocket = accept(masterSocket,
						 (struct sockaddr *)&clientIPAddress,
						 (socklen_t*)&alen);

			if (slaveSocket == -1) {
				continue;
			}

			// single threaded
			if (mode == 0) {
				if (slaveSocket < 0) {
					perror("accept");
					exit(-1);
				}

				// Process request.	
				processRequest(slaveSocket);

				// Close socket
				close(slaveSocket);
			}

			// process based
			else if (mode == 1) {
				pid_t slave = fork();
				if (slave == 0) {
					processRequest(slaveSocket);
					close(slaveSocket);
					exit(EXIT_SUCCESS);
				}

				close(slaveSocket);
			}

			// thread based
			else if (mode == 2) {
				// thread attributes initialization 
				pthread_t tid;
				pthread_attr_t attr;

				pthread_attr_init( &attr );
				pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);

				// create thread
				pthread_create(&tid, &attr, (void * (*)(void *)) processRequestThread, (void *) slaveSocket);
			}
		}	
	}
}

void processRequestThread(int socket) {
	processRequest(socket);
	close(socket);
}

void poolSlave(int socket) {
	while (1) {
		// Accept incoming connections
		struct sockaddr_in clientIPAddress;
		int alen = sizeof(clientIPAddress);
	
		pthread_mutex_lock(&mutex); 
		int slaveSocket = accept(socket,
						 (struct sockaddr *)&clientIPAddress,
						 (socklen_t*)&alen);
		pthread_mutex_unlock(&mutex); 

		processRequest(slaveSocket);
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
	memset(docPath, 0, sizeof(docPath));
	
	int length = 0;
	char currString[1024];
	memset(currString, 0, sizeof(currString));
	
	// read request header
	while (n = read(socket, &newChar, sizeof(newChar))) {			
		if (newChar == ' ') {
			// if it's first space, we've finished reading GET
			// and can start reading the docPath			
			if (gotGet == 0) {
				gotGet = 1;
			}
			// if it's second space (and we haven't got docPath yet)
			// we know we've finished reading docPath and we can store it
			else if (gotDP == 0) {
				length++;
				currString[length-1] = '\0';
				strcpy(docPath, currString);
				gotDP = 1;
			}
		}
		// end of header, break out of loop
		else if (oldChar == '\n' && newChar == '\r') {
			break;
		}
		// store newChar in oldChar so we can check for EOH
		// and if we've encountered GET, store newChar in currString
		// because it's effectively building docPath
		else {
			oldChar = newChar;
			if (gotGet == 1) {
				length++;
				currString[length-1] = newChar;
			}		
		}	
	}

	/****************************************
	 * Get details of request now, i.e.
	 * where the file lives.
	 ****************************************/

	// first get CWD (where files are)
	char *myCwd = {0};
	myCwd = getcwd(myCwd, 256);

	char *myCwd2 = {0};
	myCwd2 = getcwd(myCwd2, 256);
	strcat(myCwd2, "/http-root-dir");

	int i = 1;
	char begin[1024];
	memset(begin, 0, sizeof(begin));

	bool isRoot = false;

	// if "/", just return index.html
	if (strcmp(docPath, "/") == 0) {
		strcat(myCwd, "/http-root-dir/htdocs/index.html");
		isRoot = true;
	}
	// if not, check the beginning to see
	// if it is in one of our folders
	else {	
		// get the first part of the path
		while (docPath[i] != '/' && docPath[i] != '\0') {
			begin[i-1] = docPath[i];
			i++;
		} 
		begin[i] = '\0';
		
		// check the beginning against folder names
		// and build full path
		if (strcmp(begin, "icons") == 0) {
			strcat(myCwd, "/http-root-dir");
			strcat(myCwd, docPath);
		}
		else if (strcmp(begin, "htdocs") == 0) {
			strcat(myCwd, "/http-root-dir");
			strcat(myCwd, docPath);
		}
		else {
			strcat(myCwd, "/http-root-dir/htdocs");
			strcat(myCwd, docPath);
		}
	}

	/**********************************
	 * Expand file path.
	 **********************************/

	/*
	char buf[1024];
	memset(buf, 0, sizeof(buf));
	char *realPath = realpath(myCwd, buf);

	if (realPath) {
		strcpy(myCwd, buf);

		int len1 = strlen(myCwd);
		int len2 = strlen(myCwd2);

		if (len1 <= len2) printf("URL is not valid\n");
		else              printf("URL is valid\n");
	}
	*/

	/**********************************
	 * Now I have to determine
	 * the content type to return.
	 **********************************/
	int pathLength = strlen(docPath)-1;
	int j = 0;

	char fileExt[1024];
	memset(fileExt, 0, sizeof(fileExt));

	while (docPath[pathLength] != '.') {
		fileExt[j++] = docPath[pathLength];
		pathLength--;
	}
	fileExt[j] = '.';
	fileExt[j+1] = '\0';

	char contentType[256];
	memset(contentType, 0, sizeof(contentType));
	bool isText = true;
	
	// check file extension and set content type accordingly
	if (strcmp(fileExt, "lmth.") == 0 || strcmp(fileExt, "/lmth.") == 0 || isRoot == true) {
		strcpy(contentType, "text/html");
	}
	else if (strcmp(fileExt, "fig.") == 0 || strcmp(fileExt, "/fig.") == 0) {
		strcpy(contentType, "image/gif");
		isText = false;
	}
	else {
		strcpy(contentType, "text/plain");
	}

	// open file depending on content-type
	// ** probably not changing anything
	FILE * document;
	if (isText == true) {
		document = fopen(myCwd, "r");
	}
	else {
		document = fopen(myCwd, "rb");
	}
	
	if (document <= 0) {
		// send 404 if file isn't found
		const char *notFound = "File not found.";
		write(socket, "HTTP/1.0", strlen("HTTP/1.0"));
		write(socket, " ", 1);
		write(socket, "404", 3);
		write(socket, "File", 4);
		write(socket, " ", 1);
		write(socket, "Not", 3);
		write(socket, " ", 1);
		write(socket, "Found,", 6);
		write(socket, "\r\n", 2);
		write(socket, "Server:", 7);
		write(socket, " ", 1);
		write(socket, "CS 252 Lab 5", strlen("CS 252 Lab 5"));
		write(socket, "\r\n", 2);
		write(socket, "Content-type:", 13);
		write(socket, " ", 1);
		write(socket, "text/plain", strlen("text/plain"));
		write(socket, "\r\n", 2);
		write(socket, "\r\n", 2);
		write(socket, notFound, strlen(notFound));
	}
	else {
		// get the fd of the requested file
		int fd = fileno(document);

		if (fd == -1) ;
		else {
			write(socket, "HTTP/1.0", strlen("HTTP/1.0"));
			write(socket, " ", 1);
			write(socket, "200 ", 4);
			write(socket, "Document", strlen("Document"));
			write(socket, " ", 1);
			write(socket, "follows", 7);
			write(socket, "\r\n", 2);
			write(socket, "Server:", 7);
			write(socket, " ", 1);
			write(socket, "CS 252 Lab 5", strlen("CS 252 Lab 5"));
			write(socket, "\r\n", 2);
			write(socket, "Content-Type:", strlen("Content-Type:"));
			write(socket, " ", 1);
			write(socket, contentType, strlen(contentType));
			write(socket, "\r\n", 2);
			write(socket, "\r\n", 2);

			char c;
			int count = 0;

			// read the file and write it back
			while (count = read(fd, &c, sizeof(c))) {
				write(socket, &c, sizeof(c));
			}	
		}
	}
}
