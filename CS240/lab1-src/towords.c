/***************************
 * Word Counter            *
 * written by Joe Martella *
 * September 10, 2010      *
 ***************************/

#include <stdio.h>

int main(int argc, char ** argv) {
	int counter = 0;				// word counter
	int i = 0;					// incrementable variable for for loop
	char c;						// current character
	int cCounter = 0; 				// character counter

	printf("Program to separate text to words. Type a string and ctrl-d to exit\n");

	// reads in characters from keyboard
	while ((c = getchar()) != EOF){                 // checks for ctrl+d
		if (cCounter == 0){			// checks if it's a  new line
			if (c != EOF){			// checks we haven't reach end of file
				printf("Word %d: ", counter);
				printf("%c", c);
				counter++;			// increment word counter
				cCounter++;			// increment character counter			
			}
		}
		else if ((c == ' ') || (c == '\n')){    // checks for a space or a new line
				for (i = 0; ((c = getchar()) == ' ') || (c == '\n'); i++) // gets chars 
				;						// until != a space or newline		
			if (c != EOF){
				printf("\nWord %d: ", counter);
				printf("%c", c);
				counter++;			// increment word counter
				cCounter++;			// increment character counter
			}
		}
		else if (c == '\n'){				// if new lines, clears character counter
			cCounter = 0;
		}
		else{ 					// if not a space, print character 
			printf("%c", c);		// and increment character counter
			cCounter++;		
		}

	}

	printf("\nwords total = %d\n", counter);		// print word counter

	return 0;
}
