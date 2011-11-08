
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

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;


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

	// just display docPath for my own benefit
	// printf("docPath is: %s\n", &docPath);
	
	/****************************************
	 * Get details of request now, i.e.
	 * where the file lives.
	 ****************************************/

	// first get CWD (where files are)
	char *myCwd = {0};
	myCwd = getcwd(myCwd, 256);

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
		while (docPath[i] != '/') {
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

	// just display cwd for my own benefit
	// printf("cwd is: %s\n", myCwd);


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

	// display content type for my own benefit
	// printf("content type is: %s\n", contentType);
	
	
	FILE * document;
	if (isText == true) {
		document = fopen(myCwd, "r");
	}
	else {
		document = fopen(myCwd, "rb");
	}
	
	if (document == 0) {
		//printf("Could not open file.\n");
		const char *notFound = "No no, we don't gots that file, yo!";
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
		write(socket, "Joserver", 9);
		write(socket, "\r\n", 2);
		write(socket, "Content-type:", 13);
		write(socket, " ", 1);
		write(socket, contentType, sizeof(contentType));
		write(socket, "\r\n", 2);
		write(socket, "\r\n", 2);
		write(socket, notFound, strlen(notFound));
	}
	else {
		//printf("Opened a file.\n");
		int fd = fileno(document);
		//printf("fd = %d\n", fd);
		
		// stores size of file
		char szS[1024];
		memset(szS,0,sizeof(szS));
		
		// gets file size
		fseek(document, 0L, SEEK_END);
		long sz = ftell(document);
		fseek(document, 0L, SEEK_SET);
		sprintf(szS, "%d", sz);
		// printf("file size: %s\n", szS);
		

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
			write(socket, "lore", strlen("lore"));
			write(socket, "\r\n", 2);
			write(socket, "Content-Type:", strlen("Content-Type:"));
			write(socket, " ", 1);
			write(socket, contentType, strlen(contentType));
			//write(socket, "\r\n", 2);
			/*write(socket, "Content-Length:", strlen("Content-Length:"));
			write(socket, " ", 1);
			write(socket, szS, strlen(szS));*/
			write(socket, "\r\n", 2);
			write(socket, "\r\n", 2);

			char c;
			//memset(c,0,sizeof(c));
			int count = 0;
			int f = 0;

			// printf("%s\n", contentType);

			// uses read/write if html or text
			if (isText == true) {
				while (count = read(fd, &c, sizeof(c))) {
					write(socket, &c, sizeof(c));
				}
			}
			// uses this for images
			else {
				// writes image files
				char * data;
				data = (char *) malloc (sizeof(char)*sz);		
				memset(data, 0, sizeof(data));

				FILE * sock = fdopen(socket, "wb");
				int n;

				size_t result = fread(data, 1, sz, document);
				if (result != sz) {
					printf("Reading error.\n");
				}
				else {
					int bytesWritten = 0;
					if ((bytesWritten = fwrite (data, 1, result, sock)) != sz) {
						perror("Write");
					}
					else {
						printf("Bytes written: %d\n", bytesWritten);
					}
				}
				
				fclose(document);
			}
			
		}
	}
}
