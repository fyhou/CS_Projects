
/*
 * CS354: Shell project
 *
 * Template file.
 * You will need to add more code here to execute the command table.
 *
 * NOTE: You are responsible for fixing any bugs this code may have!
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#include "command.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
extern char **environ; 

SimpleCommand::SimpleCommand()
{
	// Creat available space for 5 arguments
	_numberOfAvailableArguments = 5;
	_numberOfArguments = 0;
	_executeMe = 1;
	_arguments = (char **) malloc( _numberOfAvailableArguments * sizeof( char * ) );
}

void
SimpleCommand::insertArgument( char * argument )
{
	if ( _numberOfAvailableArguments == _numberOfArguments  + 1 ) {
		// Double the available space
		_numberOfAvailableArguments *= 2;
		_arguments = (char **) realloc( _arguments,
				  _numberOfAvailableArguments * sizeof( char * ) );
	}

	char * sVarName = (char *) malloc (1024 * sizeof(char));
	int nVarName = 0;

	char * sVarValue = (char *) malloc ( 1024 * sizeof(char));

	char * sNewArg = (char *) malloc (1024 * sizeof(char));
	int nNewArg = 0;
	// ${C}p${D}
	for (int i = 0; i < argument[i] != '\0'; i++) {
		if (argument[i] == '$' && argument[i+1] == '{') {
			i = i + 2;
			while (argument[i] != '}') {
				sVarName[nVarName++] = argument[i++];
			}
			
			sVarName[nVarName] = '\0';

			sVarValue = getenv(strdup(sVarName));
			strcat(sNewArg, sVarValue); 

			nNewArg = nNewArg + strlen(sVarValue);
			memset(sVarValue, 0, sizeof(sVarValue));
			memset(sVarName, 0, sizeof(sVarName));
			nVarName = 0;		
		}
		else {
			sNewArg[nNewArg++] = argument[i]; 
		}
	}

	// tilde expansion
	if (sNewArg[0] == '~') {
		if (sNewArg[1] == '\0') {
			struct passwd *pw = getpwuid(getuid());

			const char *homedir = pw->pw_dir;
			memcpy(sNewArg, homedir, strlen(homedir)+1);
		}
		else {
			if (strchr(sNewArg, '/') == NULL) {
				char *name = (char*) malloc (1024*sizeof(char));
				name = ++sNewArg;
				//printf("name = %s\n", name);
				--sNewArg;

				struct passwd *pw = getpwnam(name);

				const char *homedir = pw->pw_dir;
				//printf("dirname = %s\n", homedir);
				memcpy(sNewArg, homedir, strlen(homedir)+1);
			}
			else {
				char * nameAndDir = (char*) malloc (1024*sizeof(char));
				nameAndDir = ++sNewArg;
				--sNewArg;

				char * name = (char*) malloc (1024 * sizeof(char));
				int end = 0;
				for (int i = 0; nameAndDir[i] != '/'; i++) {		
					name[i] = nameAndDir[i];
					end = i + 1;
				}
				name[end] = '\0';
				
				char * dir = (char*) malloc (1024*sizeof(char));
				int end2 = 0;
				for (int i = end; nameAndDir[i] != '\0'; i++) {
					dir[end2++] = nameAndDir[i];
				}
				dir[end2] = '\0';

				struct passwd *pw = getpwnam(name);

				char *homedir = pw->pw_dir;
				
				strcat(homedir, dir);
				memcpy(sNewArg, homedir, strlen(homedir)+1);
			}
		}
	}

	_arguments[ _numberOfArguments ] = strdup(sNewArg);

	// Add NULL argument at the end
	_arguments[ _numberOfArguments + 1] = NULL;
	
	_numberOfArguments++;
}

Command::Command()
{
	// Create available space for one simple command
	_numberOfAvailableSimpleCommands = 1;
	_simpleCommands = (SimpleCommand **)
		malloc( _numberOfSimpleCommands * sizeof( SimpleCommand * ) );

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
	_append = 0;
}

void
Command::insertSimpleCommand( SimpleCommand * simpleCommand )
{
	if ( _numberOfAvailableSimpleCommands == _numberOfSimpleCommands ) {
		_numberOfAvailableSimpleCommands *= 2;
		_simpleCommands = (SimpleCommand **) realloc( _simpleCommands,
			 _numberOfAvailableSimpleCommands * sizeof( SimpleCommand * ) );
	}
	
	_simpleCommands[ _numberOfSimpleCommands ] = simpleCommand;
	_numberOfSimpleCommands++;
}

void
Command:: clear()
{
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		for ( int j = 0; j < _simpleCommands[ i ]->_numberOfArguments; j ++ ) {
			free ( _simpleCommands[ i ]->_arguments[ j ] );
		}
		
		free ( _simpleCommands[ i ]->_arguments );
		free ( _simpleCommands[ i ] );
	}

	if ( _outFile ) {
		free( _outFile );
	}

	if ( _inputFile ) {
		free( _inputFile );
	}

	if ( _errFile ) {
		free( _errFile );
	}

	_numberOfSimpleCommands = 0;
	_outFile = 0;
	_inputFile = 0;
	_errFile = 0;
	_background = 0;
}

void
Command::print()
{
	printf("\n\n");
	printf("              COMMAND TABLE                \n");
	printf("\n");
	printf("  #   Simple Commands\n");
	printf("  --- ----------------------------------------------------------\n");
	
	for ( int i = 0; i < _numberOfSimpleCommands; i++ ) {
		printf("  %-3d ", i );
		for ( int j = 0; j < _simpleCommands[i]->_numberOfArguments; j++ ) {
			printf("\"%s\" \t", _simpleCommands[i]->_arguments[ j ] );
		}
		printf("\n");
	}

	printf( "\n\n" );
	printf( "  Output       Input        Error        Background\n" );
	printf( "  ------------ ------------ ------------ ------------\n" );
	printf( "  %-12s %-12s %-12s %-12s\n", _outFile?_outFile:"default",
		_inputFile?_inputFile:"default", _errFile?_errFile:"default",
		_background?"YES":"NO");
	printf( "\n\n" );
}

void
Command::execute()
{
	// Don't do anything if there are no simple commands
	if ( _numberOfSimpleCommands == 0 ) {
		prompt();
		return;
	}

	// Print contents of Command data structure
	//print();

	// Add execution here
	// For every simple command fork a new process
	// Setup i/o redirection
	// and call exec

	// saving default in/out/err
	int tmpin = dup(0);
	int tmpout = dup(1);
	int tmperr = dup(2);

	// set initial input
	int fdin;
	if (_inputFile) {
		fdin = open(_inputFile, O_RDONLY, 0700);
	}
	else {
		fdin = dup(tmpin);	
	}

	int ret;
	int fdout;
	int fderr;

	for (int i = 0; i < _numberOfSimpleCommands; i++) {
		if (_simpleCommands[i]->_executeMe == 0) {
			//continue;
		}

		// set input
		dup2(fdin, 0);
		close(fdin);

		// set the output if it's the last command
		if (i == _numberOfSimpleCommands-1) {
			if (_outFile) {
				if (_append == 0) {
					fdout = open(_outFile, O_WRONLY|O_CREAT|O_TRUNC, 0700);
				}
				else {
					fdout = open(_outFile, O_WRONLY|O_CREAT|O_APPEND, 0700);
				}
			}
			else {
				fdout=dup(tmpout);
			}
		}
		// not the last command...
		else {
			int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[0];
			fdin=fdpipe[1];
			
		}

		// set the error if it's the last command
		if (i == _numberOfSimpleCommands-1) {
			if (_errFile) {
				if (_append == 0) {
					fderr = open(_errFile, O_WRONLY|O_CREAT|O_TRUNC, 0700);
				}
				else {
					fderr = open(_errFile, O_WRONLY|O_CREAT|O_APPEND, 0700);
				}
			}
			else {
				fderr=dup(tmperr);
			}

			dup2(fderr,2);
			close(fderr);
		}

		dup2(fdout,1);
		close(fdout);
		
		// set environment variables if necessary
		if (!strcmp(_simpleCommands[i]->_arguments[0], "setenv")) {	
			setenv(_simpleCommands[i]->_arguments[1], _simpleCommands[i]->_arguments[2], 1);
			clear();
			prompt();
			return;
		}

		// set environment variables if necessary
		if (!strcmp(_simpleCommands[i]->_arguments[0], "cd")) {	
			int cd;
			if (_simpleCommands[0]->_arguments[1] == NULL) {
				struct passwd *pw = getpwuid(getuid());
				const char *homeDirectory = pw->pw_dir;
				cd = chdir(homeDirectory);
			}
			else {
				cd = chdir(_simpleCommands[0]->_arguments[1]);
			}

			if (cd != 0) {
				perror("chdir");
			}

			clear();
			prompt();
			return;
		}

		// unset environment variables if necessary
		if (!strcmp(_simpleCommands[i]->_arguments[0], "unsetenv")) {
			unsetenv(_simpleCommands[i]->_arguments[1]);
			clear();
			prompt();
			return;
		}

		// create a new process
		ret = fork();

		if (ret == 0) {
			if (!strcmp(_simpleCommands[i]->_arguments[0], "printenv")) {
				char **p = environ;
				while (*p!=NULL) {
					printf("%s\n", *p);
					p++;
				}
				exit(0);
			}

			// child process
			execvp(_simpleCommands[i]->_arguments[0], _simpleCommands[i]->_arguments);
			perror("execvp");
			_exit(1);
		}
		else if (ret < 0) {
			// there was an error in fork 
			perror("fork");
			exit(2);
		}
		else {
			// parent process
			// ret is the pid of the child
			// wait until the child exits	
		}
	}

	// restore back to default
	dup2(tmpin, 0);
	dup2(tmpout,1);
	dup2(tmperr,2);

	// close dem defaults
	close(tmpin);
	close(tmpout);
	close(tmperr);	

	if (_background == 0) {
		waitpid(ret, 0, 0);
	}

	// Clear to prepare for next command
	clear();
	
	// Print new prompt
	prompt();
}

// Shell implementation

void
Command::prompt()
{
	if (isatty(0)) {
		printf("myshell>");
		fflush(stdout);
	}
}

extern "C" void disp( int sig )
{
	printf("\n");
	Command::_currentCommand.prompt();
}

extern "C" void killzombie( int sig )
{
	while(waitpid(-1, NULL, WNOHANG) > 0); 
}

Command Command::_currentCommand;
SimpleCommand * Command::_currentSimpleCommand;

int yyparse(void);

main()
{
	struct sigaction signalAction;
	signalAction.sa_handler = disp;
	sigemptyset(&signalAction.sa_mask);
	signalAction.sa_flags = SA_RESTART;
	int error = sigaction(SIGINT, &signalAction, NULL );
	if ( error )
	{
		perror( "sigaction" );
		exit( -1 );
	}

	struct sigaction signalAction2;
	signalAction2.sa_handler = killzombie;
	sigemptyset(&signalAction2.sa_mask);
	signalAction2.sa_flags = SA_RESTART;
	int error2 = sigaction(SIGCHLD, &signalAction2, NULL );
	if ( error2 )
	{
		perror( "sigaction" );
		exit( -1 );
	}

	Command::_currentCommand.prompt();
	yyparse();
}

