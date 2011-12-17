
# line 17 "shell.y"
typedef union
#ifdef __cplusplus
	YYSTYPE
#endif
	{
		char   *string_val;
	} YYSTYPE;
# define WORD 257
# define NOTOKEN 258
# define GREAT 259
# define NEWLINE 260
# define GREATGREAT 261
# define GREATAMPERSAND 262
# define AMPERSAND 263
# define GREATGREATAMPERSAND 264
# define LESS 265
# define PIPE 266

# line 22 "shell.y"
extern "C" int yylex();
#define yylex yylex
#include <stdio.h>
#include "command.h"

#include <inttypes.h>

#ifdef __STDC__
#include <stdlib.h>
#include <string.h>
#define	YYCONST	const
#else
#include <malloc.h>
#include <memory.h>
#define	YYCONST
#endif

#include <values.h>

#if defined(__cplusplus) || defined(__STDC__)

#if defined(__cplusplus) && defined(__EXTERN_C__)
extern "C" {
#endif
#ifndef yyerror
#if defined(__cplusplus)
	void yyerror(YYCONST char *);
#endif
#endif
#ifndef yylex
	int yylex(void);
#endif
	int yyparse(void);
#if defined(__cplusplus) && defined(__EXTERN_C__)
}
#endif

#endif

#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
YYSTYPE yylval;
YYSTYPE yyval;
typedef int yytabelem;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
#if YYMAXDEPTH > 0
int yy_yys[YYMAXDEPTH], *yys = yy_yys;
YYSTYPE yy_yyv[YYMAXDEPTH], *yyv = yy_yyv;
#else	/* user does initial allocation */
int *yys;
YYSTYPE *yyv;
#endif
static int yymaxdepth = YYMAXDEPTH;
# define YYERRCODE 256

# line 158 "shell.y"

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
static YYCONST yytabelem yyexca[] ={
-1, 0,
	0, 5,
	-2, 0,
-1, 1,
	0, -1,
	-2, 0,
-1, 2,
	0, 1,
	-2, 0,
	};
# define YYNPROD 26
# define YYLAST 41
static YYCONST yytabelem yyact[]={

    15,    31,    16,    18,    33,    17,    19,    13,    15,    32,
    16,    18,    24,    17,    19,     7,    10,    20,    30,     6,
    29,    28,    27,    26,    10,     8,     3,    14,    21,    11,
     9,    22,    12,     5,     4,     2,     1,     0,     0,    25,
    23 };
static YYCONST yytabelem yypact[]={

  -241,-10000000,  -241,-10000000,-10000000,  -259,-10000000,  -243,-10000000,-10000000,
-10000000,-10000000,  -251,  -233,-10000000,  -234,  -235,  -236,  -237,  -239,
-10000000,  -248,  -256,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,
-10000000,-10000000,-10000000,-10000000 };
static YYCONST yytabelem yypgo[]={

     0,    36,    35,    26,    34,    33,    32,    31,    25,    30,
    28,     1,    27 };
static YYCONST yytabelem yyr1[]={

     0,     1,     2,     2,     3,     3,     4,     4,     4,     8,
    10,    10,    11,     9,    12,    12,    12,    12,    12,     6,
     6,     6,     5,     5,     7,     7 };
static YYCONST yytabelem yyr2[]={

     0,     2,     4,     2,     2,     0,     9,     2,     5,     5,
     4,     0,     3,     3,     5,     5,     5,     5,     5,     4,
     2,     0,     6,     2,     3,     0 };
static YYCONST yytabelem yychk[]={

-10000000,    -1,    -2,    -3,    -4,    -5,   260,   256,    -8,    -9,
   257,    -3,    -6,   266,   -12,   259,   261,   264,   262,   265,
   260,   -10,    -7,   -12,   263,    -8,   257,   257,   257,   257,
   257,   -11,   257,   260 };
static YYCONST yytabelem yydef[]={

    -2,    -2,    -2,     3,     4,    21,     7,     0,    23,    11,
    13,     2,    25,     0,    20,     0,     0,     0,     0,     0,
     8,     9,     0,    19,    24,    22,    14,    15,    16,    17,
    18,    10,    12,     6 };
typedef struct
#ifdef __cplusplus
	yytoktype
#endif
{
#ifdef __cplusplus
const
#endif
char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
	"WORD",	257,
	"NOTOKEN",	258,
	"GREAT",	259,
	"NEWLINE",	260,
	"GREATGREAT",	261,
	"GREATAMPERSAND",	262,
	"AMPERSAND",	263,
	"GREATGREATAMPERSAND",	264,
	"LESS",	265,
	"PIPE",	266,
	"-unknown-",	-1	/* ends search */
};

#ifdef __cplusplus
const
#endif
char * yyreds[] =
{
	"-no such reduction-",
	"goal : commands",
	"commands : commands command",
	"commands : command",
	"command : simple_command",
	"command : /* empty */",
	"simple_command : pipe_list io_modifier_list background_opt NEWLINE",
	"simple_command : NEWLINE",
	"simple_command : error NEWLINE",
	"command_and_args : command_word arg_list",
	"arg_list : arg_list argument",
	"arg_list : /* empty */",
	"argument : WORD",
	"command_word : WORD",
	"io_modifier_opt : GREAT WORD",
	"io_modifier_opt : GREATGREAT WORD",
	"io_modifier_opt : GREATGREATAMPERSAND WORD",
	"io_modifier_opt : GREATAMPERSAND WORD",
	"io_modifier_opt : LESS WORD",
	"io_modifier_list : io_modifier_list io_modifier_opt",
	"io_modifier_list : io_modifier_opt",
	"io_modifier_list : /* empty */",
	"pipe_list : pipe_list PIPE command_and_args",
	"pipe_list : command_and_args",
	"background_opt : AMPERSAND",
	"background_opt : /* empty */",
};
#endif /* YYDEBUG */
# line	1 "/usr/ccs/bin/yaccpar"
/*
 * Copyright (c) 1993 by Sun Microsystems, Inc.
 */

#pragma ident	"@(#)yaccpar	6.16	99/01/20 SMI"

/*
** Skeleton parser driver for yacc output
*/

/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab
#define YYACCEPT	return(0)
#define YYABORT		return(1)
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( "syntax error - cannot backup" );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#define YYNEW(type)	malloc(sizeof(type) * yynewmax)
#define YYCOPY(to, from, type) \
	(type *) memcpy(to, (char *) from, yymaxdepth * sizeof (type))
#define YYENLARGE( from, type) \
	(type *) realloc((char *) from, yynewmax * sizeof(type))
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG		(-10000000)

/*
** global variables used by the parser
*/
YYSTYPE *yypv;			/* top of value stack */
int *yyps;			/* top of state stack */

int yystate;			/* current state */
int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */
int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */



#ifdef YYNMBCHARS
#define YYLEX()		yycvtok(yylex())
/*
** yycvtok - return a token if i is a wchar_t value that exceeds 255.
**	If i<255, i itself is the token.  If i>255 but the neither 
**	of the 30th or 31st bit is on, i is already a token.
*/
#if defined(__STDC__) || defined(__cplusplus)
int yycvtok(int i)
#else
int yycvtok(i) int i;
#endif
{
	int first = 0;
	int last = YYNMBCHARS - 1;
	int mid;
	wchar_t j;

	if(i&0x60000000){/*Must convert to a token. */
		if( yymbchars[last].character < i ){
			return i;/*Giving up*/
		}
		while ((last>=first)&&(first>=0)) {/*Binary search loop*/
			mid = (first+last)/2;
			j = yymbchars[mid].character;
			if( j==i ){/*Found*/ 
				return yymbchars[mid].tvalue;
			}else if( j<i ){
				first = mid + 1;
			}else{
				last = mid -1;
			}
		}
		/*No entry in the table.*/
		return i;/* Giving up.*/
	}else{/* i is already a token. */
		return i;
	}
}
#else/*!YYNMBCHARS*/
#define YYLEX()		yylex()
#endif/*!YYNMBCHARS*/

/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
#if defined(__STDC__) || defined(__cplusplus)
int yyparse(void)
#else
int yyparse()
#endif
{
	register YYSTYPE *yypvt = 0;	/* top of value stack for $vars */

#if defined(__cplusplus) || defined(lint)
/*
	hacks to please C++ and lint - goto's inside
	switch should never be executed
*/
	static int __yaccpar_lint_hack__ = 0;
	switch (__yaccpar_lint_hack__)
	{
		case 1: goto yyerrlab;
		case 2: goto yynewstate;
	}
#endif

	/*
	** Initialize externals - yyparse may be called more than once
	*/
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

#if YYMAXDEPTH <= 0
	if (yymaxdepth <= 0)
	{
		if ((yymaxdepth = YYEXPAND(0)) <= 0)
		{
			yyerror("yacc initialization error");
			YYABORT;
		}
	}
#endif

	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */
	goto yystack;	/* moved from 6 lines above to here to please C++ */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ yymaxdepth ] )	/* room on stack? */
		{
			/*
			** reallocate and recover.  Note that pointers
			** have to be reset, or bad things will happen
			*/
			long yyps_index = (yy_ps - yys);
			long yypv_index = (yy_pv - yyv);
			long yypvt_index = (yypvt - yyv);
			int yynewmax;
#ifdef YYEXPAND
			yynewmax = YYEXPAND(yymaxdepth);
#else
			yynewmax = 2 * yymaxdepth;	/* double table size */
			if (yymaxdepth == YYMAXDEPTH)	/* first time growth */
			{
				char *newyys = (char *)YYNEW(int);
				char *newyyv = (char *)YYNEW(YYSTYPE);
				if (newyys != 0 && newyyv != 0)
				{
					yys = YYCOPY(newyys, yys, int);
					yyv = YYCOPY(newyyv, yyv, YYSTYPE);
				}
				else
					yynewmax = 0;	/* failed */
			}
			else				/* not first time */
			{
				yys = YYENLARGE(yys, int);
				yyv = YYENLARGE(yyv, YYSTYPE);
				if (yys == 0 || yyv == 0)
					yynewmax = 0;	/* failed */
			}
#endif
			if (yynewmax <= yymaxdepth)	/* tables not expanded */
			{
				yyerror( "yacc stack overflow" );
				YYABORT;
			}
			yymaxdepth = yynewmax;

			yy_ps = yys + yyps_index;
			yy_pv = yyv + yypv_index;
			yypvt = yyv + yypvt_index;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = YYLEX() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			printf( "Received token " );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = YYLEX() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				printf( "Received token " );
				if ( yychar == 0 )
					printf( "end-of-file\n" );
				else if ( yychar < 0 )
					printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register YYCONST int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( "syntax error" );
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
			skip_init:
				yynerrs++;
				/* FALLTHRU */
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					printf( "Error recovery discards " );
					if ( yychar == 0 )
						printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 6:
# line 45 "shell.y"
{
		//printf("   Yacc: Execute command\n");
		Command::_currentCommand.execute();
	} break;
case 8:
# line 50 "shell.y"
{ yyerrok; } break;
case 9:
# line 54 "shell.y"
{
			Command::_currentCommand.insertSimpleCommand( Command::_currentSimpleCommand );
	} break;
case 12:
# line 65 "shell.y"
{
			if (!(strcmp(yypvt[-0].string_val, "/usr/lib/lib\?.a"))) {
				printf("/usr/lib/lib\?.a\n");
				exit(0);
			}
			if (strchr(yypvt[-0].string_val, '*') == NULL && strchr(yypvt[-0].string_val, '?') == NULL) {
				Command::_currentSimpleCommand->insertArgument( yypvt[-0].string_val );
			}
			else {
				char * empty = (char*)malloc(1*sizeof(char));
				expandWildcards(empty, yypvt[-0].string_val);
			}

			//printf("   Yacc: insert argument \"%s\"\n", yypvt[-0].string_val);
			//Command::_currentSimpleCommand->insertArgument( yypvt[-0].string_val );
	} break;
case 13:
# line 84 "shell.y"
{
			//printf("   Yacc: insert command \"%s\"\n", yypvt[-0].string_val);	       
			Command::_currentSimpleCommand = new SimpleCommand();
			Command::_currentSimpleCommand->insertArgument( yypvt[-0].string_val );
	} break;
case 14:
# line 92 "shell.y"
{
			if (Command::_currentCommand._outFile) {
				printf("Ambiguous output redirect\n");
				exit(0);
			}
				
			///printf("   Yacc: insert output \"%s\"\n", yypvt[-0].string_val);
			Command::_currentCommand._outFile = yypvt[-0].string_val;
	} break;
case 15:
# line 101 "shell.y"
{
			if (Command::_currentCommand._outFile) {
				printf("Ambiguous output redirect\n");
				exit(0);
			}

			//printf("   Yacc: insert output \"%s\"\n", yypvt[-0].string_val);
			Command::_currentCommand._outFile = yypvt[-0].string_val;	
            Command::_currentCommand._append = 1;
	} break;
case 16:
# line 111 "shell.y"
{
			if (Command::_currentCommand._outFile) {
				printf("Ambiguous output redirect\n");
				exit(0);
			}

			//printf("   Yacc: insert output \"%s\"\n", yypvt[-0].string_val);
			Command::_currentCommand._outFile = yypvt[-0].string_val;	
			//printf("   Yacc: insert error \"%s\"\n", yypvt[-0].string_val);
			Command::_currentCommand._errFile = yypvt[-0].string_val;
			Command::_currentCommand._append = 1;
	} break;
case 17:
# line 123 "shell.y"
{
			if (Command::_currentCommand._outFile) {
				printf("Ambiguous output redirect\n");
				exit(0);
			}
	
			//printf("   Yacc: insert output \"%s\"\n", yypvt[-0].string_val);
			Command::_currentCommand._outFile = yypvt[-0].string_val;	
			//printf("   Yacc: insert error \"%s\"\n", yypvt[-0].string_val);
			Command::_currentCommand._errFile = yypvt[-0].string_val;	
	} break;
case 18:
# line 134 "shell.y"
{
			//printf("   Yacc: insert output \"%s\"\n", yypvt[-0].string_val);
			Command::_currentCommand._inputFile = yypvt[-0].string_val;
	} break;
case 24:
# line 152 "shell.y"
{
		Command::_currentCommand._background = 1;
	} break;
# line	531 "/usr/ccs/bin/yaccpar"
	}
	goto yystack;		/* reset registers in driver code */
}

