
const char * usage =
"                                                               \n"
"talk-server:                                                \n"
"                                                               \n"
"Simple server program used to communicate multiple users       \n"
"                                                               \n"
"To use it in one window type:                                  \n"
"                                                               \n"
"   talk-server <port>                                       \n"
"                                                               \n"
"Where 1024 < port < 65536.             \n"
"                                                               \n"
"In another window type:                                       \n"
"                                                               \n"
"   telnet <host> <port>                                        \n"
"                                                               \n"
"where <host> is the name of the machine where talk-server  \n"
"is running. <port> is the port number you used when you run   \n"
"daytime-server.                                               \n"
"                                                               \n";

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "linked_list.h"

// Here are some variables ot help you in the programming of the talk-server.
// Using them is not mandatory. You may replace them/modify them as you want.

char * user;
char * password;
char * host;
char * args;

#define PASSWORD_FILE "password.txt"
LINKED_LIST * users;
LINKED_LIST * usersInRoom;

typedef struct MESSAGE {
	char * user;
	char * message;
	int secs;
} MESSAGE;

// List of messages. They wrap around
#define MAX_MESSAGES 100
int nmessages;
int lastMessage;
int nMessagesOverall;
MESSAGE messages[MAX_MESSAGES];

int QueueLength = 5;

// Processes time request
void initialize();
void processRequest( int socket );
void addUser(int fd, char * user, char * password, char * args);
void enterRoom(int fd, char * user, char * password, char * args);
void leaveRoom(int fd, char * user, char * password, char * args);
void sendMessage(int fd, char * user, char * password, char * args);
void getMessages(int fd, char * user, char * password, char * args);
void getUsersInRoom(int fd, char * user, char * password, char * args);
void getAllUsers(int fd, char * user, char * password, char * args);

int open_server_socket(int port) {

	// Set the IP address and port for this server
	struct sockaddr_in serverIPAddress; 
	memset( &serverIPAddress, 0, sizeof(serverIPAddress) );
	serverIPAddress.sin_family = AF_INET;
	serverIPAddress.sin_addr.s_addr = INADDR_ANY;
	serverIPAddress.sin_port = htons((u_short) port);
  
	// Allocate a socket
	int masterSocket =  socket(PF_INET, SOCK_STREAM, 0);
	if ( masterSocket < 0) {
		perror("socket");
		exit( -1 );
	}

	// Set socket options to reuse port. Otherwise we will
	// have to wait about 2 minutes before reusing the sae port number
	int optval = 1; 
	int err = setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, 
			     (char *) &optval, sizeof( int ) );
	
	// Bind the socket to the IP address and port
	int error = bind( masterSocket,
			  (struct sockaddr *)&serverIPAddress,
			  sizeof(serverIPAddress) );
	if ( error ) {
		perror("bind");
		exit( -1 );
	}
	
	// Put socket in listening mode and set the 
	// size of the queue of unprocessed connections
	error = listen( masterSocket, QueueLength);
	if ( error ) {
		perror("listen");
		exit( -1 );
	}

	return masterSocket;
}

int
main( int argc, char ** argv )
{
	// Print usage if not enough arguments
	if ( argc < 2 ) {
		fprintf( stderr, "%s", usage );
		exit( -1 );
	}
	
	// Get the port from the arguments
	int port = atoi( argv[1] );
	
	int masterSocket = open_server_socket(port);

	initialize();
	
	while ( 1 ) {
		
		// Accept incoming connections
		struct sockaddr_in clientIPAddress;
		int alen = sizeof( clientIPAddress );
		int slaveSocket = accept( masterSocket,
					  (struct sockaddr *)&clientIPAddress,
					  (socklen_t*)&alen);
		
		if ( slaveSocket < 0 ) {
			perror( "accept" );
			exit( -1 );
		}
		
		// Process request.
		processRequest( slaveSocket );		
	}
}

//
// Commands:
//   Commands are started y the client.
//
//   Request: ADD-USER <USER> <PASSWD>\r\n
//   Answer: OK\r\n or DENIED\r\n
//
//    REQUEST: GET-ALL-USERS <USER> <PASSWD>\r\n
//    Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//
//   Request: ENTER-ROOM <USER> <PASSWD>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: LEAVE-ROOM <USER> <PASSWD>\r\n
//   Answer: OK\n or DENIED\r\n
//
//   Request: SEND-MESSAGE <USER> <PASSWD> <MESSAGE>\n
//   Answer: OK\n or DENIED\n
//
//   Request: GET-MESSAGES <USER> <PASSWD> <LAST-MESSAGE-SECS>\r\n
//   Answer: SECS1 USER1 MESSAGE1\r\n
//           SECS2 USER2 MESSAGE2\r\n
//           SECS3 USER2 MESSAGE2\r\n
//           ...\r\n
//           \r\n
//
//    REQUEST: GET-USERS-IN-ROOM <USER> <PASSWD>\r\n
//    Answer: USER1\r\n
//            USER2\r\n
//            ...
//            \r\n
//

void
processRequest( int fd )
{
	// Buffer used to store the comand received from the client
	const int MaxCommandLine = 1024;
	char commandLine[ MaxCommandLine + 1 ];
	int commandLineLength = 0;
	int n;
	
	// Currently character read
	unsigned char prevChar = 0;
	unsigned char newChar = 0;
	
	//
	// The client should send COMMAND-LINE\n
	// Read the name of the client character by character until a
	// \n is found.
	//

	// Read character by character until a \n is found or the command string is full.
	while ( commandLineLength < MaxCommandLine &&
		read( fd, &newChar, 1) > 0 ) {

		if (newChar == '\n' && prevChar == '\r') {
			break;
		}
		
		commandLine[ commandLineLength ] = newChar;
		commandLineLength++;

		prevChar = newChar;
	}
	
	// Add null character at the end of the string
	// Eliminate last \r
	commandLineLength--;
        commandLine[ commandLineLength ] = 0;

	// The commandLine has the following format:
	// COMMAND <user> <password> <arguments>. See below.
	// You need to separate the commandLine into those components
	char c;
	int i = 0;
	char * command = malloc (50*sizeof(char));
	user = malloc (50*sizeof(char));
	password = malloc (50*sizeof(char));
	args = malloc (100*sizeof(char));
	int part = 1;
	int j = 0;
	int x = 0;

	for (i = 0; i < 100; i++) {
		if (commandLine[i] == ' ' && part != 4) {
			part++;
			j = 0;
		}
		else if (commandLine[i] == '\r') {
			break;
		}
		else if (part == 1) {
			command[j++] = commandLine[i];
		}
		else if (part == 2) {
			user[j++] = commandLine[i];
		}
		else if (part == 3) {
			password[j++] = commandLine[i];
		}
		else if (part == 4) {
			args[j++] = commandLine[i];
		}
		else {
			break;
		}
	}

	//write(fd, command, strlen(command));
	//write(fd, "\n", 1);

	// For now, command, user, and password are hardwired.
	//char * command = "ADD-USER";
	//user = "peter";
	//password = "spider";
	if (args[0] == '\0') {
		args = "";
	}

	printf("command=%s\n", command);
	printf("user=%s\n", user);
	printf( "password=%s\n", password );
	printf("args=%s\n", args);

	if (!strcmp(command, "ADD-USER")) {
		addUser(fd, user, password, args);
	}
	else if (!strcmp(command, "ENTER-ROOM")) {
		enterRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "LEAVE-ROOM")) {
		leaveRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "SEND-MESSAGE")) {
		sendMessage(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-MESSAGES")) {
		getMessages(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-USERS-IN-ROOM")) {
		getUsersInRoom(fd, user, password, args);
	}
	else if (!strcmp(command, "GET-ALL-USERS")) {
		getAllUsers(fd, user, password, args);
	}
	else {
		const char * msg =  "UNKNOWN COMMAND\r\n";
		write(fd, msg, strlen(msg));
	}

	// Send OK answer
	// const char * msg =  "OK\n";
	// write(fd, msg, strlen(msg));

	memset(command, 0, 1000);
	memset(user, 0, 1000);
	memset(password, 0, 1000);
	memset(commandLine, 0, 1000);
	free(command);
	free(user);
	free(password);

	close(fd);	
}

void initialize()
{
	// Open password file
	FILE *file;
	file = fopen(PASSWORD_FILE, "w+");

	// Initialize users in room
	usersInRoom = llist_create();
	users = llist_create();

	// Initalize message list
	nmessages = 0;
	for (nmessages = 0; nmessages < 100; nmessages++) {
		messages[nmessages].user = malloc (50*sizeof(char));
		messages[nmessages].message = malloc (50*sizeof(char));
	}
	nmessages = 1;
}

int checkPassword(int fd, char * user, char * password) {
	// Here check the password
	char test[100];
	if ((llist_lookup(users,user)) == NULL) {
		return 0;
	}
	else {

		strcpy (test, llist_lookup(users, user));
		if ((strcmp(test, password)) == 0) {
		return 1;
		}
		else { 
			return 0;		
		}
	}
}

void addUser(int fd, char * user, char * password, char * args)
{
	// Here add a new user. For now always return OK.
	llist_add(users, user, password);	
	llist_save(users, PASSWORD_FILE);
	const char * msg =  "OK\r\n";
	write(fd, msg, strlen(msg));

	return;		
}

void enterRoom(int fd, char * user, char * password, char * args)
{
	if ((checkPassword(fd,user,password)) == 1) {
		if (!llist_add(usersInRoom, user, password)) {
			const char * msg = "OK\r\n";
			strcpy(messages[nmessages].user,user);
			strcpy(messages[nmessages].message, " entered the room.\r\n");
			messages[nmessages].secs = nmessages; 
			write(fd, msg, strlen(msg));
			nmessages++;
		}
		else {
			const char * msg = "DENIED\r\n";
			write(fd, msg, strlen(msg));
		}
	}
	else {
		const char * msg = "ERROR (Wrong password)\r\n";
		write(fd,msg,strlen(msg));
	}
	return;
	
}

void leaveRoom(int fd, char * user, char * password, char * args)
{
	if ((checkPassword(fd,user,password)) == 1) {
		if((llist_remove(usersInRoom, user)) == 1) {
			const char * msg = "OK\r\n";
			write(fd,msg,strlen(msg));
			strcpy(messages[nmessages].user,user);
			strcpy(messages[nmessages].message, " left the room\r\n");
			messages[nmessages].secs = nmessages;
			nmessages++;
		}
		else {
			const char * msg = "OK\r\n";
			write(fd,msg,strlen(msg));
		}
	}
	else {
		const char * msg = "ERROR (Wrong password)\r\n";
		write(fd,msg,strlen(msg));
	}
	return;
}

void sendMessage(int fd, char * user, char * password, char * args)
{
	if ((checkPassword(fd,user,password)) == 1) {
		if ((llist_lookup(usersInRoom, user)) != NULL) {
			strcpy(messages[nmessages].user,user);
			strcat(args, "\r\n");
			strcpy(messages[nmessages].message, args);
			messages[nmessages].secs = nmessages;
			nmessages++;
			const char * msg = "OK\r\n";
			write(fd, msg, strlen(msg));
		}
		else {
			const char * msg = "DENIED (not in room)\r\n";
			write(fd, msg, strlen(msg));
		}
	}
	else {
		const char * msg = "ERROR (Wrong password)\r\n";
		write (fd,msg,strlen(msg));
	}
	return;
}

void getMessages(int fd, char * user, char * password, char * args)
{
	char number[10]; 
	int i = 0;
	char c;
	int argy = atoi(args);
	argy++;
	char * test;

	if ((checkPassword(fd,user,password)) == 1) {
		if ((llist_lookup(usersInRoom, user)) == NULL) {
			const char * msg = "DENIED (not in room)\r\n";
			write(fd, msg, strlen(msg));
		}
		else {
			for (i = argy; i < nmessages; i++) {
				snprintf(number,sizeof(number), "%d", i);
				if (i < 10) 
					write(fd, number, 1);
				else 
					write(fd, number, 2);
				write(fd, " ", 1);
				write(fd, messages[i].user, strlen(messages[i].user));
				write(fd, " ", 1);	
				write(fd, messages[i].message, strlen(messages[i].message));
			}
			write(fd,"\r\n", sizeof("\r\n"));
		}
	}
	else {
		const char * msg = "ERROR (Wrong password)\r\n";
		write(fd,msg,strlen(msg));
	}
	return;
}

void getUsersInRoom(int fd, char * user, char * password, char * args)
{
	if ((checkPassword(fd,user,password)) == 1) {
		if ((llist_lookup(usersInRoom, user)) == NULL) {
			const char * msg = "DENIED (not in room)\r\n";
			write(fd,msg,strlen(msg));
		}
		else {
			LINKED_LIST_ENTRY * e;
			e = usersInRoom->head->next;
			while (e != usersInRoom->head) {
				write(fd, e->name, strlen(e->name));
				write(fd,"\r\n",2);
				e = e->next;
			}
			write(fd,"\r\n",2);
		}
	}
	else {
		const char * msg = "ERROR (Wrong password)\r\n";
		write(fd,msg,strlen(msg));
	}
}

void getAllUsers(int fd, char * user, char * password, char * args)
{
	if ((checkPassword(fd,user,password)) == 1) {
		LINKED_LIST_ENTRY * e;
		e = users->head->next;
		while ( e != users->head) {
			write(fd, e->name, strlen(e->name));
			write(fd, "\r\n", 2);
			e = e->next;
		}
		write(fd,"\r\n",2);
		close(fd);
	}
	else {
		const char * msg = "ERROR (Wrong password)\r\n";
		write(fd,msg,strlen(msg));
	}
}

// check password (if YES : then NO)
