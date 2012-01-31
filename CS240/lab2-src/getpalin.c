/**************************************
* Palindromes: Part 2 of Lab 2	      *
* written by Joe Martella	      *
* September 20, 2010		      *
***************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverse (char *c);				// reverse function
char reverse_arr[100];					// static array to hold reverse number
int reverse_counter = 0; 				// step counter

/************************************
* Main function that takes in a     *
* number and produces a palindrome. *
* MF				    *
*************************************/
int main(int argc, char **argv) {
	int length = 0;
	if (argc == 2)
		length = strlen(argv[1]);		// length of number
	char original_arr[32];				// array to hold original 
	char *reverse_ptr;				// pointer to reverse array
	int original_int = 0;				// number to work with
	int reverse_int = 0;				// number to work with
	int first_input = 0; 				// stores first input
	int str_compare = 1; 				// 0 if strings are equal

	// checks if an input was enterted
	if (argc == 2)
		strcpy(original_arr, argv[1]);
	else {
		printf("Usage: getpalin <number>\n");
		return;
	}

	char *orig_ptr = &original_arr[length-1];	// points to last element of number array

	// points to the reverse array
	reverse_ptr = reverse(orig_ptr);

	// points orig_ptr back to beginning of original_arr
	orig_ptr = &original_arr[0];

	// makes arrays into ints to work with
	original_int = atoi(orig_ptr);
	first_input = original_int;
	reverse_int = atoi(reverse_ptr);

	// input check
	if (original_int < 10 || original_int > 1000){
		printf("%d Please provide a number between 10 and 1000.\n", original_int);
		return;
	}

	// let's get a palindrome!
	while (str_compare != 0 && reverse_counter <= 12){
		sprintf(original_arr, "%d", original_int + reverse_int);	// makes number into an array
		int length2 = strlen(original_arr);				// gets length of new number
		orig_ptr = &original_arr[length2-1];				// points to last element of array
		reverse_ptr = reverse(orig_ptr);				// flips the array
		reverse_arr[length2] = NULL;					// deletes garbage char

		orig_ptr = &original_arr[0];					// sets pointer to first element
		reverse_ptr = &reverse_arr[0];					// sets pointer to first element

		original_int = atoi(orig_ptr);					// makes new ints to work with
		reverse_int = atoi(reverse_ptr);				// makes new ints to work with

		reverse_counter++;						// step counter
		str_compare = strcmp(orig_ptr, reverse_ptr);			// compares given strings; 0 if same
	}

	// if palindrome was found within 12 steps
	if (reverse_counter <= 12)
		printf("%d %d %d\n", first_input, atoi(original_arr), reverse_counter);	
	// if no palindrome was found within 12 steps
	else
		printf("%d 0 0\n", first_input);

	return 0;
}

/************************************
* Reverses a string of numbers      *
* @param char* pointer to original  *
* @return char* pointer to reverse  *
* F1				    *
*************************************/
char *reverse (char *orig_ptr){
	char *reverse_ptr = &reverse_arr[0];				// points to reverse_arr	
	int i = 0;							// counter

	// a swap function between last element of original array
	// to the first element of the reverse array.
	for (i = 0; i < 32; i++){
		reverse_arr[i] = *orig_ptr;
		orig_ptr--;
	}

	reverse_ptr = &reverse_arr[0];					// points to first element in reverse array
	return	reverse_ptr;
}
