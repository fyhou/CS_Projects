#include <assert.h>
#include <string.h>
#include <stdio.h>

char *mystrcpy(char * s1, const char * s2);
size_t mystrlen(const char *s);
char *mystrdup(const char *s1);
char *mystrcat(char * s1, const char * s2);
char *mystrstr(char * s1, const char * s2);
int mystrcmp(const char *s1, const char *s2) ;

int
main()
{
  char s1[64], *s2;
  char s3[64], *s4;

  /* TRIVIAL tests -- you should extend these or you are likely to
   * lose points in grading. */

 /*
	NOTE: Testing the input of erroneous types (i.e. int, 
	double) was executed and received segmentation faults, 
	but so do the library functions, so task was still 
	achieved.
  */

  /* Test mystrcpy */
  mystrcpy (s1, "Hello world");
  assert(!strcmp (s1, "Hello world"));
  assert(strcmp (s1, "Hello worl"));
  assert(strcmp (s1, "Hello worldgggg"));

  /* Additional test: empty string */
  mystrcpy (s3, "");
  assert(!strcmp(s3, ""));
  assert(strcmp (s3, "test"));

  mystrcpy (s1, "");
  assert(!strcmp (mystrcpy (s1, ""), ""));

  /* Test mystrlen */
  assert (mystrlen("Hello world") == 11);
  assert (mystrlen("Hello world") == 11);

  assert (mystrlen("Hello world") == 11);
  assert (mystrlen("Hello world") == 11);

  /* Additional test: empty string */
  assert (mystrlen("") == 0);
 
  /* Test strdup */
  s2 = mystrdup("Hello world");
  assert( !strcmp(s2, "Hello world") );
  s2[0]='Y';
  assert( !strcmp(s2, "Yello world") );
  free(s2);

  /* Additional test: empty string */
  s4 = mystrdup("");
  assert(!strcmp(s4, ""));
  assert(strcmp(s4, "test"));

  // Test mystrcat
  mystrcpy(s1, "Purdue");
  mystrcat(s1, " University");
  assert( !strcmp(s1, "Purdue University")); 

  mystrcat(s1, "");
  assert( !strcmp(s1, "Purdue University")); 

  // Test mystrstr
  mystrcpy(s1, "The quick brown fox jumps over the lazy dog");
  s2 = mystrstr(s1, "jumps");
  assert(!strcmp(s2, "jumps over the lazy dog")); 
  assert(mystrstr(s1, "Hello")==NULL);
  assert(mystrstr("jumps", s1)==NULL);
  s2 = mystrstr(s1, "");
  assert(s2 == s1);

//int mystrcmp(const char *s1, const char *s2) ;
 // Test strcmp
  assert(mystrcmp("abcd","dabc")<0);
  assert(mystrcmp("dab", "abcd")>0);
  assert(mystrcmp("dab", "dab")==0);

  /* Additional test: empty string */
  assert(mystrcmp("", "A") < 0);
  assert(mystrcmp("", "") == 0);

  /* Additional test: different casings */
  assert(mystrcmp("AA", "aa") < 0);
  assert(!mystrcmp("a", "A") == 0);


  printf ("Seems to be OK\n");
  return 0;
}
