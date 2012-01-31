/*********************************
 * RPN Calculator                *
 * written by Joe Martella  	 *
 * September 10, 2010		 *
 *********************************/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char ** argv)
{
	float stack[argc*argc];		// "stack" used for storing
	int i = 0;			// integer to increment through argv[]
	int head = 0; 			// integer to increment though stack[]
	float num1;			// variable to hold stack value for operations
	float num2;			// another variable to hold a stack value for operations
	int usageCheck = 0;             // lets program know if any arguments were entered

	for (i = 1; i < argc ; i++){				// reads through the command line arguments
		if (argv[i][0] == '+'){				// if it's a plus, it reads the last two
			num1 = (stack[head-2]);			// numbers in the stack, adds them, and places
			num2 = (stack[head-1]);			// back in the stack.
			stack[head-2] = (num1 + num2);
			head--;
			usageCheck = 1;
		}
		else if (argv[i][0] == '-'){			// if it's a negative sign, it checks the next
			if (argv[i][1] == '\0'){		// character to see if it's a \0 to signify it's 
				num1 = (stack[head-2]);		// a subtraction sign, but if it has a number after 
				num2 = (stack[head-1]);		// it, it's a negative number; if subtraction, does
				stack[head-2] = (num1 - num2);	// subtraction process; if negative, number gets placed
				head--;
				usageCheck = 1; 		// in the stack
			}
			else{
				stack[head] = atof(argv[i]); 
				head++;
				usageCheck = 1;
			}
		}
		else if (argv[i][0] == 'x'){			// if it's an x, it does the multiplication
			num1 = (stack[head-2]);			// necessary for RPN
			num2 = (stack[head-1]);
			stack[head-2] = (num1 * num2);	
			head--;
			usageCheck = 1;
		}
		else if (argv[i][0] == '/'){			// if it's a /, it does the division necessay
			num1 = (stack[head-2]);			// for RPN
			num2 = (stack[head-1]);
			stack[head-2] = (num1 / num2);
			head--;
			usageCheck = 1;
		}
		else if (argv[i][0] == 'c'){			// if it's a c, it takes the cosine of the head
			num1 = (stack[head-1]);			// of the stack.
			stack[head-1] = cosf(num1);
			usageCheck = 1;
		}
		else if (argv[i][0] == 's'){			// if it's an s, it takes the sine of the head
			num1 = (stack[head-1]);			// of the stack.
			stack[head-1] = sinf(num1);
			usageCheck = 1;
		}
		else if (argv[i][0] == 'p'){			// if it's a p, it raises the second number in the
			num1 = (stack[head-2]);			// stack to the power of the head of the stack.
			num2 = (stack[head-1]);
			stack[head-2] = powf(num1, num2);
			head--;
			usageCheck = 1;
		}
		else if (argv[i][0] == 'e'){			// if it's an e, it does e^head of the stack.
			num1 = (stack[head-1]);
			stack[head-1] = expf(num1);
			usageCheck = 1;
		}
		else if (argv[i][0] == 'l'){			// if it's an l, it does the natural log of 
			num1 = (stack[head-1]);			// the head of the stack.
			stack[head-1] = logf(num1);
			usageCheck = 1;
		}
		else{
			stack[head] = atof(argv[i]);		// if it is a digit, the argument is pushed onto 
			head++;					// the stack.
			usageCheck = 1;				// usageCheck variable is set to 1 to let program
		}						// know that at least one argument was placed in the 
	}							// stack.
	
	if (usageCheck == 0)					// if usageCheck == 0, it means no digits were entered.
		printf("Usage: rpncalc op1 op2 ...\n");
	else if (head == 1)					// if the head is equal to 1, that means the 
		printf("%f\n", stack[0]);			// answer is reached and is printed out.
	else if (head > 1)					// if the head > 1, it means there is more than one 
		printf("Elements remain in the stack\n");	// element left in the stack.
	else							// if the head < 1, it means too many operations were
		printf("Stack underflow\n");			// entered and not enough digits exist to complete them.
	return 0;
}
