#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# ifndef YYLMAX 
# define YYLMAX BUFSIZ
# endif 
#ifndef __cplusplus
# define output(c) (void)putc(c,yyout)
#else
# define lex_output(c) (void)putc(c,yyout)
#endif

#if defined(__cplusplus) || defined(__STDC__)

#if defined(__cplusplus) && defined(__EXTERN_C__)
extern "C" {
#endif
	int yyback(int *, int);
	int yyinput(void);
	int yylook(void);
	void yyoutput(int);
	int yyracc(int);
	int yyreject(void);
	void yyunput(int);
	int yylex(void);
#ifdef YYLEX_E
	void yywoutput(wchar_t);
	wchar_t yywinput(void);
#endif
#ifndef yyless
	int yyless(int);
#endif
#ifndef yywrap
	int yywrap(void);
#endif
#ifdef LEXDEBUG
	void allprint(char);
	void sprint(char *);
#endif
#if defined(__cplusplus) && defined(__EXTERN_C__)
}
#endif

#ifdef __cplusplus
extern "C" {
#endif
	void exit(int);
#ifdef __cplusplus
}
#endif

#endif
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
#ifndef __cplusplus
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
#else
# define lex_input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
#endif
#define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng;
#define YYISARRAY
char yytext[YYLMAX];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;

# line 3 "shell.l"
/*
 *
 * CS-413 Spring 98
 * shell.l: lexical analyzer for shell
 * You have to extend it.
 *
 */

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

# define YYNEWLINE 10
int yylex(){
int nstr; extern int yyprevious;
#ifdef __cplusplus
/* to avoid CC and lint complaining yyfussy not being used ...*/
static int __lex_hack = 0;
if (__lex_hack) goto yyfussy;
#endif
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:

# line 50 "shell.l"
	{
		return NEWLINE;
	}
break;
case 2:

# line 54 "shell.l"
	{
		/* Discard spaces and tabs */
     	}
break;
case 3:

# line 58 "shell.l"
	{
		return GREAT;
	}
break;
case 4:

# line 62 "shell.l"
{ return GREATGREAT; }
break;
case 5:

# line 64 "shell.l"
{ return GREATAMPERSAND; }
break;
case 6:

# line 66 "shell.l"
{ return GREATGREATAMPERSAND; }
break;
case 7:

# line 68 "shell.l"
{ return LESS; }
break;
case 8:

# line 70 "shell.l"
{ return PIPE; }
break;
case 9:

# line 72 "shell.l"
{ return AMPERSAND; }
break;
case 10:

# line 74 "shell.l"
{
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
break;
case 11:

# line 95 "shell.l"
   {
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
break;
case 12:

# line 112 "shell.l"
   {
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
break;
case 13:

# line 243 "shell.l"
   {
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
break;
case 14:

# line 268 "shell.l"
  {
		/* Assume that file names have only alpha chars */
		yylval.string_val = strdup(yytext);
		return WORD;
	}
break;
case 15:

# line 274 "shell.l"
{
		/* Invalid character in input */
		return NOTOKEN;
	}
break;
case -1:
break;
default:
(void)fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */

# line 280 "shell.l"

int yyvstop[] = {
0,

14,
15,
0, 

2,
15,
0, 

1,
0, 

14,
15,
0, 

9,
15,
0, 

7,
15,
0, 

3,
15,
0, 

13,
14,
15,
0, 

14,
15,
0, 

8,
15,
0, 

14,
0, 

13,
14,
0, 

14,
0, 

10,
11,
14,
0, 

13,
14,
0, 

5,
0, 

4,
0, 

13,
0, 

14,
0, 

13,
14,
0, 

12,
14,
0, 

10,
11,
0, 

10,
11,
13,
14,
0, 

13,
0, 

6,
0, 

12,
0, 

13,
0, 

12,
13,
14,
0, 

10,
11,
13,
0, 

12,
13,
0, 
0};
# define YYTYPE unsigned char
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	1,3,	0,0,	
6,15,	0,0,	0,0,	3,13,	
0,0,	11,22,	1,4,	1,5,	
6,16,	6,0,	10,14,	3,0,	
3,0,	11,23,	11,0,	15,0,	
0,0,	0,0,	10,0,	10,0,	
0,0,	13,0,	13,0,	14,0,	
14,0,	22,0,	17,0,	17,0,	
27,0,	27,0,	0,0,	1,6,	
0,0,	6,17,	3,0,	1,7,	
3,13,	6,16,	11,22,	9,19,	
3,0,	10,0,	11,23,	10,14,	
13,0,	16,16,	14,0,	10,21,	
20,29,	17,0,	13,0,	27,0,	
0,0,	16,16,	16,0,	17,0,	
0,0,	1,8,	2,8,	1,9,	
2,9,	0,0,	3,0,	9,20,	
3,0,	0,0,	18,18,	0,0,	
0,0,	0,0,	0,0,	0,0,	
13,0,	0,0,	13,0,	18,0,	
0,0,	17,0,	16,26,	17,0,	
0,0,	0,0,	16,16,	24,24,	
0,0,	32,0,	32,0,	0,0,	
0,0,	1,10,	2,10,	6,18,	
24,0,	1,11,	3,14,	6,15,	
11,24,	15,18,	3,13,	18,27,	
11,25,	0,0,	21,21,	18,28,	
13,14,	10,14,	23,23,	22,24,	
32,0,	17,14,	21,0,	21,0,	
0,0,	0,0,	23,23,	23,0,	
24,24,	0,0,	28,28,	0,0,	
24,31,	1,12,	2,12,	25,0,	
25,0,	31,31,	3,0,	28,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	21,0,	31,0,	21,21,	
13,0,	0,0,	0,0,	23,23,	
16,16,	17,0,	0,0,	23,23,	
0,0,	0,0,	25,0,	0,0,	
33,21,	0,0,	0,0,	28,33,	
25,0,	0,0,	0,0,	28,28,	
33,0,	33,0,	31,31,	34,21,	
0,0,	18,18,	31,31,	0,0,	
0,0,	0,0,	0,0,	34,0,	
34,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	25,0,	0,0,	
25,0,	0,0,	24,32,	33,0,	
0,0,	33,21,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	34,0,	0,0,	
34,21,	0,0,	0,0,	0,0,	
0,0,	21,21,	0,0,	0,0,	
0,0,	23,30,	0,0,	0,0,	
0,0,	0,0,	25,14,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	28,28,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
31,34,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	25,0,	0,0,	
0,0,	0,0,	0,0,	33,21,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	34,21,	0,0,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-2,	yysvec+1,	0,	
yycrank+-6,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+4,
yycrank+0,	0,		yyvstop+7,
yycrank+-3,	0,		yyvstop+9,
yycrank+0,	0,		yyvstop+12,
yycrank+0,	0,		yyvstop+15,
yycrank+5,	0,		yyvstop+18,
yycrank+-13,	0,		yyvstop+21,
yycrank+-8,	0,		yyvstop+25,
yycrank+0,	0,		yyvstop+28,
yycrank+-16,	yysvec+3,	yyvstop+31,
yycrank+-18,	yysvec+10,	yyvstop+33,
yycrank+-9,	yysvec+6,	yyvstop+36,
yycrank+-48,	0,		0,	
yycrank+-21,	yysvec+3,	yyvstop+38,
yycrank+-69,	yysvec+16,	yyvstop+42,
yycrank+0,	0,		yyvstop+45,
yycrank+14,	0,		yyvstop+47,
yycrank+-105,	yysvec+10,	yyvstop+49,
yycrank+-19,	yysvec+11,	yyvstop+51,
yycrank+-109,	0,		0,	
yycrank+-86,	yysvec+23,	yyvstop+53,
yycrank+-118,	yysvec+3,	yyvstop+56,
yycrank+0,	0,		yyvstop+59,
yycrank+-23,	yysvec+10,	yyvstop+62,
yycrank+-121,	yysvec+16,	yyvstop+67,
yycrank+0,	0,		yyvstop+69,
yycrank+0,	0,		yyvstop+71,
yycrank+-128,	yysvec+23,	yyvstop+73,
yycrank+-80,	yysvec+10,	yyvstop+75,
yycrank+-151,	yysvec+10,	yyvstop+79,
yycrank+-162,	yysvec+10,	yyvstop+83,
0,	0,	0};
struct yywork *yytop = yycrank+258;
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
  0,   1,   1,   1,   1,   1,   1,   1, 
  1,   9,  10,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  9,   1,  34,   1,   1,   1,  38,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,  38,   1,  38,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
 96,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,  38,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
  1,   1,   1,   1,   1,   1,   1,   1, 
0};
char yyextra[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/*	Copyright (c) 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*	THIS IS UNPUBLISHED PROPRIETARY SOURCE CODE OF AT&T	*/
/*	The copyright notice above does not evidence any   	*/
/*	actual or intended publication of such source code.	*/

#pragma ident	"@(#)ncform	6.12	97/12/08 SMI"

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
#if defined(__cplusplus) || defined(__STDC__)
int yylook(void)
#else
yylook()
#endif
{
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
#ifndef __cplusplus
			*yylastch++ = yych = input();
#else
			*yylastch++ = yych = lex_input();
#endif
#ifdef YYISARRAY
			if(yylastch > &yytext[YYLMAX]) {
				fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
				exit(1);
			}
#else
			if (yylastch >= &yytext[ yytextsz ]) {
				int	x = yylastch - yytext;

				yytextsz += YYTEXTSZINC;
				if (yytext == yy_tbuf) {
				    yytext = (char *) malloc(yytextsz);
				    memcpy(yytext, yy_tbuf, sizeof (yy_tbuf));
				}
				else
				    yytext = (char *) realloc(yytext, yytextsz);
				if (!yytext) {
				    fprintf(yyout,
					"Cannot realloc yytext\n");
				    exit(1);
				}
				yylastch = yytext + x;
			}
#endif
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (uintptr_t)yyt > (uintptr_t)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((uintptr_t)yyt < (uintptr_t)yycrank) {	/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					if(lsp > &yylstate[YYLMAX]) {
						fprintf(yyout,"Input string too long, limit %d\n",YYLMAX);
						exit(1);
					}
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
#ifndef __cplusplus
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
#else
		yyprevious = yytext[0] = lex_input();
		if (yyprevious>0)
			lex_output(yyprevious);
#endif
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
#if defined(__cplusplus) || defined(__STDC__)
int yyback(int *p, int m)
#else
yyback(p, m)
	int *p;
#endif
{
	if (p==0) return(0);
	while (*p) {
		if (*p++ == m)
			return(1);
	}
	return(0);
}
	/* the following are only used in the lex library */
#if defined(__cplusplus) || defined(__STDC__)
int yyinput(void)
#else
yyinput()
#endif
{
#ifndef __cplusplus
	return(input());
#else
	return(lex_input());
#endif
	}
#if defined(__cplusplus) || defined(__STDC__)
void yyoutput(int c)
#else
yyoutput(c)
  int c; 
#endif
{
#ifndef __cplusplus
	output(c);
#else
	lex_output(c);
#endif
	}
#if defined(__cplusplus) || defined(__STDC__)
void yyunput(int c)
#else
yyunput(c)
   int c; 
#endif
{
	unput(c);
	}
