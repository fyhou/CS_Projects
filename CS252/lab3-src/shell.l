
/*
 *
 * CS-413 Spring 98
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

%{

#include <string.h>
#include "y.tab.h"

////////////  Start added code ///////////

char * read_line();

int mygetc(FILE * f) {
  static char *p;
  char ch;

  if (!isatty(0)) {
    // stdin is not a tty. Call real getc
    return getc(f);
  }

  // stdin is a tty. Call our read_line.

  if (p==NULL || *p == 0) {
    char * s = read_line();
    p = s;
  }

  ch = *p;
  p++;

  return ch;
}

#undef getc
#define getc(f) mygetc(f)

/////////// End added code ///////////

%}

%%

\n 	{
		return NEWLINE;
	}

[ \t] 	{
		/* Discard spaces and tabs */
     	}	

">" 	{
		return GREAT;
	}

">>" { return GREATGREAT; }

">&" { return GREATAMPERSAND; }

">>&" { return GREATGREATAMPERSAND; }

"<" { return LESS; }

"|" { return PIPE; }

"&" { return AMPERSAND; }

\"[^\n\"]*\" {
	int end = 0;
	int i = 0;
	
	while ( yytext[i] != '\0' ) {
		if (i == 0) {		
			i++;
			//printf("here1\n");
			continue;
		}

		yylval.string_val[i-1] = yytext[i];
		//printf("%c\n", yytext[i]);
		end = i;
		i++;
	}

	yylval.string_val[end-1] = '\0';
	return WORD;
}

\"[^\n\"]*\"    {
        /* quoted string */
        char *new_string = (char*)malloc(sizeof(char) * 1028);
        int i = 0;
        int j = 0;
        for(i = 0; yytext[i] != '\0'; i++){
            if(yytext[i] == 34){
                continue;
            }
            new_string[j] = yytext[i];
            j++;
        }
        //fprintf(stderr, "%s\n\n", new_string);
        yylval.string_val = strdup(new_string);
        free(new_string);
        return WORD;
    }   
`[^\n`]*`    {
        char buffer[1024];

        /* backticks */
        char *commands = (char*) malloc(sizeof(char) * 1024);
        int i = 0;
        int j = 0;
        for(i = 0; yytext[i] != '\0'; i++){
            if(yytext[i] == '`'){
                continue;
            }
            commands[j] = yytext[i];
            j++;
        }
        commands[j] = '\n';
        j++;

		// pass another exit to ensure exiting
        char sExit[5] = "exit\n";
        for(i = 0; sExit[i] != '\0'; i++){
            commands[j] = sExit[i];
            j++;
        }
        j++;
        commands[j] = '\0';
       
        // preserve stdin and stdout
        int tmpin = dup(0);
        int tmpout = dup(1);
       
        // create pipe for transferring commands/results
        int parentPipe[2];
        int childPipe[2];
       
        if(pipe(parentPipe) == -1){
            perror("pipe");
            exit(2);
        }
        if(pipe(childPipe) == -1){
            perror("pipe");
            exit(2);
        }   
       
       
        // parent stdin to parentPipe[0]
        dup2(parentPipe[0],0);
        close(parentPipe[0]);

        // parent stdout to childPipe[1]
        dup2(childPipe[1],1);
        close(childPipe[1]);
       
		// fork the new process
        int ret = fork();
       
        if(ret == 0){
            // child stdin to childpipe[0]
            dup2(childPipe[0],0);
            close(childPipe[0]);
           
            // child output to parent so it can pass results back
            dup2(parentPipe[1],1);
            close(parentPipe[1]);
 
			// run the subshell
            char *arguments[2];
            arguments[0] = "shell";
            arguments[1] = NULL;
            execvp(arguments[0], arguments);
           
            perror("execvp");
           
            exit(1);
        }else if(ret < 0){
            perror("fork");
            exit(1);
        }else{
            int count = 0;

            for (count = 0; count <= strlen(commands); count++)
            {
                write(1,commands+count,1);
            }

            dup2(tmpout, 1);
            close(tmpout);

            close(parentPipe[1]);
            close(parentPipe[0]);

            close(childPipe[1]);
            close(childPipe[0]);
           
            int k = 0;
            char c = 0;   
            while (read(0, &c, 1) != 0)
            {
                if (c == '\n')
                {
                    buffer[k] = ' ';
                }
                else
                {
                    //grow buffer if necessary
                    buffer[k] = c;
                }
                k++;
            }
            buffer[k] = '\0';
           
            dup2(tmpin, 0);
            close(tmpin);

            close(parentPipe[1]);
            close(parentPipe[0]);
            close(childPipe[1]);
            close(childPipe[0]);
        }
       
       
        waitpid(ret, NULL, 0);
       
        int c = 0;
        int length = strlen(buffer);
        while (c < length)
        {
            unput(buffer[length - 1 - c]);
            c++;
        }
    }

[^ \t\n&<>\|]*\\[^ \t\n]*    {
        /* escape characters */
        char *sNewArg = (char*) malloc(1024*sizeof(char));

        int i = 0; int j = 0;

        for(i = 0; i != strlen(yytext); i++){
            if(yytext[i] == 92){
                // means escape char was hit
                if(yytext[i+1] == 92){
                    sNewArg[j] = yytext[i+1];
                    i++; j++;
                }
            }
			else {
            	sNewArg[j] = yytext[i];
            	j++;
			}
        }
       
        yylval.string_val = strdup(sNewArg);
        return WORD;
       
    }

[^ \t\n|><&][^ \t\n|><&]*   {
		/* Assume that file names have only alpha chars */
		yylval.string_val = strdup(yytext);
		return WORD;
	}

.	{
		/* Invalid character in input */
		return NOTOKEN;
	}

%%
	
