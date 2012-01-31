/***************************
 * Line Counter            *
 * written by Joe Martella *
 * September 10, 2010      *
 ***************************/

#include <stdio.h>

main(int argc, char ** argv) {
	int counter = 0;		// line counter
	char c;				// current character

	printf("Program to count lines. Type a string and ctrl-d to exit\n");
	while(c != EOF){		// makes sure we haven't reached the end of the file
		c = getchar();	
		if (c == '\n'){		// if there is a new line, increment the counter
			counter += 1;
		}
	} 
	printf("Total lines: %d\n", counter); // prints results
}
