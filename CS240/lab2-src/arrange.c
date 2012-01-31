/****************************************
* More Palindromes: Part 3 of Lab 2     *
* written by Joe Martella 		*
* September 23, 2010 			*
*****************************************/

#include<stdio.h>
#include<string.h>

int sort (char array[10][100], int num);	// uses bubble sort to sort a 2d array

/****************************************
* Main function reads input in from a   *
* file and determines which lines are   *
* palindromes or not, then prints all   *
* of them in a pretty triangle.         *
* MF					*
*****************************************/
int main() {
	char palindrome[10][100];		// stores palindromes
	int pal_row = 0;			// increments
	char not_palindrome[10][100];		// stores not palindromes
	int npal_row = 0;			// increments
	char end_array[4] = "END";		// end array to test against

	char orig_input[100];		// original input of current line
	int j = 0;			// increments
	char input[100];		// current line
	int i = 0; 			// increments
	char reverse_input[100]; 	// current line in reverse
	int k = 0;			// increments
	char c = '0';			// gets chars
	char *i_ptr = &input[0];	// pointer to input array
	int input_length = 0;		// input length
	int str_comp = 1;		// string compare
	int done = 0;			// arbitrary at this point

	do {
		i = 0;			// increments
		j = 0;			// increments
		k = 0;			// increments
		input_length = 0;	// the length of the input (after formatting)
		c = '0';		// to hold current char
		i_ptr = &input[0];	// points at formatted input
		str_comp = 1;		// compare variable; 0 when a palindrome
		end_array[4] = '\0';	// add null char to END array

		memset(orig_input, 0, 100);		// these three lines are functions used
		memset(input, 0, 100);			// to clear out the arrays before getting
		memset(reverse_input, 0, 100);		// any new chars to avoid getting garbage chars

		// waits until c is a new line character, mean while, all chars are being sent to input
		// makes input all lower case and takes out punctuation; formats input array so I can 
		// check if it is truly a palinddrome
		while ((c = getchar()) != '\n') {
			orig_input[j++] = c;
			if (!(isspace(c) || iscntrl(c))){
				c = tolower(c);
				if (islower(c)){
					input[i] = c;
					i_ptr = &input[i];
					i++;
					input_length++;
				}
			}
		}
		orig_input[j] = '\0'; 	// ending the string
		input[i] = '\0';	// ending the string
		input_length++;		// must account for null char

		// checks if the orig_input (unformatted) is equal to the 
		// end array, i.e. checks if we have reached the end of theh file.
		if(!(strcmp(orig_input, end_array))){
			done = 1;
			break;
		}
	
		// reverse the formatted input array
		for (k = 0; k < input_length-1; k++) {
			reverse_input[k] = *i_ptr;
			i_ptr--;
		}
		reverse_input[i] = '\0';

		// checks if input and reverse_input are the same
		// thus, checking if they are palindromic and then
		// places the original input of the formatted array
		// into the appropriate 2d array
		if (strcmp(input, reverse_input) == 0) {
			for (i = 0; i < 100; i++) {
				palindrome[pal_row][i] = orig_input[i];
			}
			pal_row++;
		}
		else {
			for (i = 0; i < 100; i++) {
				not_palindrome[npal_row][i] = orig_input[i];
			}
			npal_row++;
		}
	} while (done == 0);


///////////////////////////////////////////////////////////////////////////////
/////////////////	   Below is sorting and 	///////////////////////
/////////////////	   printing the arrays		//////////////////////
///////////////////////////////////////////////////////////////////////////////
	printf("\n");
	int max_l = 0;		// maximum length of an array in a 2d array
	int cur_l = 0;		// current length of an array in a 2d array
	int space = 0;		// amount of spaces that must be printed

	max_l = sort (palindrome, pal_row);	// sorts the palindrome array

	// prints palindrome array
	for (i = 0; i < pal_row; i++) {
		cur_l =  strlen(palindrome[i]);			// this and next 6 lines deals with the formatted
		if (((max_l - cur_l)%2) == 0)			// input based on the lab specifications; checks
			space = (max_l - cur_l)/2;		// if difference of max and current is even/odd
		else if (((max_l - cur_l - 1)%2) == 0)		// then prints appropriate spaces.
			space = (max_l - cur_l - 1)/2;
		for (j = 0; j < space; j++)
			printf(" ");
		for (j = 0; j < cur_l; j++) {
			printf("%c", palindrome[i][j]);
		}
		printf("\n");
	}	

	printf("\n");

	max_l = sort (not_palindrome, npal_row);	// sorts the not_palindrome array

	for (i = 0; i < npal_row; i++) {
		cur_l = strlen(not_palindrome[i]);		// same explanation as how and why I printed
		if (((max_l - cur_l)%2) == 0)			// this array like this above.
			space = (max_l - cur_l)/2;
		else if (((max_l - cur_l - 1)%2) == 0)
			space = (max_l - cur_l - 1)/2;
		for (j = 0; j < space; j++)
			printf(" ");
		for (j = 0; j < cur_l; j++) {
			printf("%c", not_palindrome[i][j]);
		}
		printf("\n");
	}

	return 0;
}


/*******************************************
* Uses bubble sort to sort a 2d array      *
* @param char[][100] 2d array to be sorted *
* @param int number of rows in 2d array    *
* @return int the maximum length of a row  *
* F1					   *
********************************************/
int sort (char array[][100], int num) {
	int i = 0;		// increments
	int j = 0;		// increments
	char temp[100];		// temp array to hold string
	
	// regular bubble sort algorithm 
	for (i = 0; i < num; i++) {
		for (j = i+1; j < num; j++) {
			if (strlen(array[i]) > strlen(array[j])) {
				strcpy(temp, array[i]);
				memset(array[i], 0, 100);
				strcpy(array[i], array[j]);
				memset(array[j], 0, 100);
				strcpy(array[j], temp);
				memset(temp, 0, 100);
			}
		}
	}

	// returns length of last line after it is sorted,
	// thus returning the max length of a line.
	return strlen(array[num-1]);
}

