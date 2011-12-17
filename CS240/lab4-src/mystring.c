
#include <stdlib.h>
#include "mystring.h"

int mystrlen(char * s) {
	char c;
	int count = 0;
	while (*s != '\0'){
		s++;
		count++;
	}
	return count;
}

char * mystrcpy(char * dest, char * src) {
	memset(dest,0,10);

	char * winner = dest;

	while (*src != '\0') {
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';

	return winner;
}

char * mystrcat(char * dest, char * src) {
	char * meghan = dest; 

	while (*dest != '\0') {
		dest++;
	}
	while (*src != '\0') {
		*dest++ = *src++;
	}
	*dest = '\0';
	return meghan;
}

int mystrcmp(char * s1, char * s2) {
	
	for(; *s1 == *s2; ++s1, ++s2)
		if(*s1 == 0)
			return 0;
	return *(unsigned char *)s1 < *(unsigned char *)s2 ? -1 : 1;
}

char * mystrstr(char * hay, char * needle) {
	int n_len = mystrlen(needle);
	int h_len = mystrlen(hay);
	int length = h_len - n_len;

	int i = 0, count = 0;
	char * n;
	char * h;

	for (i = 0; i < length; i++) {
		n = needle;
		h = hay;
		count = 0;
		while (n != '\0') {
			if (*n == *h) {
				n++;
				h++;
				count++;
				if (count == n_len) {
					return hay;
				}
				else ;
			}
			else {
				break;
			}
		}
		hay++;
	}

	return NULL;
}

char * mystrdup(char * s) {
	char *d = (char *)(malloc (mystrlen(s) + 1));
	if (d == NULL) return NULL;
	mystrcpy(d,s);
	return d;
}

char * mymemcpy(char * dest, char * src, int n)
{
	while (n--) {
		*dest++ = *src++;
	}
	return dest;
}

