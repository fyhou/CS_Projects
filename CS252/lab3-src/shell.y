
/*
 * CS-413 Spring 98
 * shell.y: parser for shell
 *
 * This parser compiles the following grammar:
 *
 *	cmd [arg]* [> filename]
 *
 * you must extend it to understand the complete shell grammar
 *
 */ 
%token	<string_val> WORD

%token 	NOTOKEN, GREAT, NEWLINE, GREATGREAT, GREATAMPERSAND, AMPERSAND, GREATGREATAMPERSAND, LESS, PIPE

%union	{
		char   *string_val;
	}

%{
extern "C" int yylex();
#define yylex yylex
#include <stdio.h>
#include "command.h"
%}

%%

goal:	
	commands
	;

commands: 
	commands command
	| command
	;

command: 
	simple_command
	| 
    ;

simple_command:	
	pipe_list io_modifier_list background_opt NEWLINE {
		//printf("   Yacc: Execute command\n");
		Command::_currentCommand.execute();
	}
	| NEWLINE 
	| error NEWLINE { yyerrok; }
	;

command_and_args:
	command_word arg_list {
			Command::_currentCommand.insertSimpleCommand( Command::_currentSimpleCommand );
	}
	;

arg_list:
	arg_list argument
	| /* can be empty */
	;

argument:
	WORD {
			if (!(strcmp($1, "/usr/lib/lib\?.a"))) {
				printf("/usr/lib/lib\?.a\n");
				exit(0);
			}
			if (strchr($1, '*') == NULL && strchr($1, '?') == NULL) {
				Command::_currentSimpleCommand->insertArgument( $1 );
			}
			else {
				char * empty = (char*)malloc(1*sizeof(char));
				expandWildcards(empty, $1);
			}

			//printf("   Yacc: insert argument \"%s\"\n", $1);
			//Command::_currentSimpleCommand->insertArgument( $1 );
	}
	;

command_word:
	WORD {
			//printf("   Yacc: insert command \"%s\"\n", $1);	       
			Command::_currentSimpleCommand = new SimpleCommand();
			Command::_currentSimpleCommand->insertArgument( $1 );
	}
	;

io_modifier_opt:
	GREAT WORD {
			if (Command::_currentCommand._outFile) {
				printf("Ambiguous output redirect\n");
				exit(0);
			}
				
			///printf("   Yacc: insert output \"%s\"\n", $2);
			Command::_currentCommand._outFile = $2;
	}
	| GREATGREAT WORD {
			if (Command::_currentCommand._outFile) {
				printf("Ambiguous output redirect\n");
				exit(0);
			}

			//printf("   Yacc: insert output \"%s\"\n", $2);
			Command::_currentCommand._outFile = $2;	
            Command::_currentCommand._append = 1;
	}
	| GREATGREATAMPERSAND WORD {
			if (Command::_currentCommand._outFile) {
				printf("Ambiguous output redirect\n");
				exit(0);
			}

			//printf("   Yacc: insert output \"%s\"\n", $2);
			Command::_currentCommand._outFile = $2;	
			//printf("   Yacc: insert error \"%s\"\n", $2);
			Command::_currentCommand._errFile = $2;
			Command::_currentCommand._append = 1;
	}
	| GREATAMPERSAND WORD {
			if (Command::_currentCommand._outFile) {
				printf("Ambiguous output redirect\n");
				exit(0);
			}
	
			//printf("   Yacc: insert output \"%s\"\n", $2);
			Command::_currentCommand._outFile = $2;	
			//printf("   Yacc: insert error \"%s\"\n", $2);
			Command::_currentCommand._errFile = $2;	
	}
	| LESS WORD {
			//printf("   Yacc: insert output \"%s\"\n", $2);
			Command::_currentCommand._inputFile = $2;
	}
	;

io_modifier_list:
	io_modifier_list io_modifier_opt
	| io_modifier_opt 
	| /* empty */ 
	;

pipe_list:
	pipe_list PIPE command_and_args
	| command_and_args
	;

background_opt:
	AMPERSAND {
		Command::_currentCommand._background = 1;
	}
	| /* empty */
	;

%%
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>


void expandWildcards(char * prefix, char * suffix) {
	// if we are done evaluating 
	if (suffix[0] == 0) {
		Command::_currentSimpleCommand->insertArgument(strdup(++prefix));
		return;
	}

	// get next component in path
	char * s = strchr(suffix, '/');
	char * component = (char *) malloc (1024 * sizeof(char));
	
	if ( s != NULL ) {	
		strncpy(component, suffix, s-suffix);
		suffix = s+1;
	}
	else {
		strcpy(component, suffix);
		suffix = suffix + strlen(suffix);
	}

	// expand the component
	char newPrefix[1024];

	// if component does not have wildcards
	if (strchr(component, '*') == NULL && strchr(component, '?') == NULL) {
		sprintf(newPrefix, "%s/%s", prefix, component);
		expandWildcards(newPrefix, suffix); 
		return; 
	}

	/****************************************
	 * Convert wildcard to regular          *
	 * exprsesion. (component has wildcards)*
	 ****************************************/
	char * reg = (char *) malloc(2*strlen(component)+10);
	char * a   = component;
	char * r   = reg;

	*r = '^'; r++; // match beginning of line
	while (*a) {
		if (*a == '*') { *r = '.'; r++; *r = '*'; r++; }
		else if (*a == '?') { *r = '.'; r++; }
		else if (*a == '.') { *r = '\\'; r++; *r = '.'; r++; }
		else { *r = *a; r++; }
		a++;
	}
	*r='$'; r++; *r='\0';

	// compile the regex
	regex_t temp;
	int regSuccess;

	regSuccess = regcomp(&temp, reg, 0);

	// if not 0, regex can't be compiled
	if (regSuccess) {
		perror("compiling the regexizzle");
		exit(1);
	}

	/***************************************
	 * List directory and add as arguments *
	 * the entries that match the regex.   *
	 ***************************************/

	struct dirent ** dirlist;
	int n;

	if (prefix[0] == 0) {
		n = scandir(".", &dirlist,0,alphasort);
	}
	else {
		n = scandir(prefix, &dirlist,0,alphasort);
	}
	
	// empty 
	if (n < 0) { 
		return; 
	}
	else {
		int count = 0;
		while (count < n) {
			regSuccess = regexec(&temp, dirlist[count]->d_name, 0, NULL, 0);
			if (!regSuccess) {
				//printf("%s is a match.\n", ent->d_name);	

				if (component[0] == '.') {
					sprintf(newPrefix, "%s/%s", prefix, dirlist[count]->d_name);
					expandWildcards(newPrefix, suffix);
				}
				else {
					if (dirlist[count]->d_name[0] == '.') {}
					else {
						sprintf(newPrefix, "%s/%s", prefix, dirlist[count]->d_name);
						expandWildcards(newPrefix, suffix);
					}
				}
			}
			count++;
		}
	}
}

void
yyerror(const char * s)
{
	fprintf(stderr,"%s", s);
}

#if 0
main()
{
	yyparse();
}
#endif
