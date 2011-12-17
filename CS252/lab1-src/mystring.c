#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>

/*
 * Implement the following string procedures.
 *
 * Type "man strstr" to find what each of the functions should do.
 *
 * For example, mystrcpy should do the same as strcpy.
 *
 * IMPORTANT: DO NOT use predefined string functions.
 */

char *mystrcpy(char * s1, const char * s2)
{	
	// copies characters from s2 to s1 until null char is reached
	while (*s2 != '\0') {;
	        *s1 = *s2;
		s1++; s2++;
	}

	*s1 = '\0';
        
	return s1;
	
}

size_t mystrlen(const char *s)
{
	size_t count = 0;
	while (*s != '\0') {
		s++;
		count++;
	}

	return count;
}

char *mystrdup(const char *s1)
{
	char * d = (char *) (malloc (mystrlen(s1) + 1));
	if (d == NULL) return NULL;
	mystrcpy(d,s1);
	return d; 
}

char *mystrcat(char * s1, const char * s2)
{
	int i = 0;
	int s1Len = 0;
	
	for (i = 0; s1[i] != '\0'; i++) {
		s1Len++;
	}

	for (i = 0; s2[i] != '\0'; i++) {
		s1[s1Len++] = s2[i];
	}

	s1[s1Len] = '\0';

	return s1; 
}

char *mystrstr(char * s1, const char * s2)
{
	if (mystrlen(s2) == 0) return s1;  

	int n_len = mystrlen(s2);
	int h_len = mystrlen(s1);
	int searchLength = h_len - n_len;

	int i = 0;
	int count = 0;
	const char * n;
	char * h;

	for (i = 0; i < searchLength; i++) {
		n = s2;
		h = s1; 
		count = 0;

		while (n != '\0') {
			if (*n == *h) {
				n++;
				h++;
				count++;
				if (count == n_len) {
					return s1;
				} 			
			}
			else {
				break;
			}		
		}
		s1++;	
	}

	return NULL; 	
}

int mystrcmp(const char *s1, const char *s2) 
{
	while (!(*s1 != *s2)) {
		if (*s1 == '\0') {
			return 0; 		
		}

		s1++; 
		s2++;	
	}

	if (*s1 > *s2) return 1;
	else return -1;
}

