#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TOLERANCE 1E-6
#define MAX_ITER 12

double f(const char* funname, double x);
double fPrime(const char* funname, double x);
void printFunction();

int main(int argc, char** argv)
{
	/////////////////////////////
	// check if usage is right //
	/////////////////////////////
	if (!(argc == 3)) {
		printf("Usage: newton <poly1|sin|xsin|poly2|imaginary> <initial guess>\n");		
		exit(1);
	}

	////////////////////////////////
	// check if function is valid //	
	////////////////////////////////
	int valid = 0;
	
	if (strcmp(argv[1], "poly1") == 0)
		valid = 1;
	else if (strcmp(argv[1], "sin") == 0)
		valid = 1;
	else if (strcmp(argv[1], "xsin") == 0)
		valid = 1;
	else if (strcmp(argv[1], "poly2") == 0)
		valid = 1;
	else if (strcmp(argv[1], "imaginary") == 0)
		valid = 1;
	else
		valid = 0;

	if (valid == 0) {
		printf("Error: %s is not a valid function name\n", argv[1]);
		exit(1);	
	}

	///////////////////
	// get an answer // 
	///////////////////
	printFunction(argv[1]);
	double start = atof(argv[2]);
	int i = 0;
	double y = f(argv[1], start);
	double y_p = fPrime(argv[1], start);
	double y_12 = y;
	double start_12 = start;

	while (fabs(y) > TOLERANCE && i <= MAX_ITER) {
		printf("At iteration %d, x=%f, y=%f, y'=%f\n", i, start, y, y_p);
		if (y_p == 0.000000) {
			printf("Error: at x=%f, f'(x)=%d\n", start, (int) y_p);
			exit(1);
		}
		start_12 = start;
		start = start - y/y_p;
		y_12 = y;
		y = f(argv[1], start);
		y_p = fPrime(argv[1], start);
		i++;
	}

	if (!(y < 0.000001 && y > -0.000001))
		printf("Error: after 12 iterations, x=%f and f(x)=%f\n", start_12, y_12); 
	else {
		printf("At iteration %d, x=%f, y=%f, and y'=%f\n", i, start, y, y_p);
		printf("Solution: iteration=%d x=%f y=%f\n", i, start, y); 	
	}

	return 0;
}

/* Prints the function in readable form */
void printFunction(const char * funname)
{
        char * func;

	if(strcmp(funname, "poly1") == 0)
	  func = "y = x^2 - 4 = 0";
	else if(strcmp(funname, "sin") == 0)
	  func = "y = sin(x)-.5 = 0";
	else if(strcmp(funname, "xsin") == 0)
	  func = "y = x*sin(x)-10 = 0";
	else if(strcmp(funname, "poly2") == 0)
	  func = "y = x^3+3*x^2+4*x-1 = 0";
	else if(strcmp(funname, "imaginary") == 0)
	  func = "y = x^2+1 = 0";
	else
	{
	  printf("Error: %s is not a valid function name\n", funname);
		exit(1);
	}

        printf("Function: %s\n", func);
}

/* Evaluates f(x) */
double f(const char* funname, double x)
{
	if(strcmp(funname, "poly1") == 0)
		return (x*x - 4);
	else if(strcmp(funname, "sin") == 0)
	  return (sin(x)-.5);
	else if(strcmp(funname, "xsin") == 0)
	  return (x*sin(x)-10);
	else if(strcmp(funname, "poly2") == 0)
	  return (x*x*x+3*x*x+4*x-1);
	else if(strcmp(funname, "imaginary") == 0)
	  return (x*x+1);
	else
	{
	  printf("Error: %s is not a valid function name\n", funname);
		exit(1);
	}
}

/* Evaluates f'(x) */
double fPrime(const char* funname, double x)
{
	if(strcmp(funname, "poly1") == 0)
		return (2*x);
	else if(strcmp(funname, "sin") == 0)
	  return (cos(x));
	else if(strcmp(funname, "xsin") == 0)
	  return (sin(x)+x*cos(x));
	else if(strcmp(funname, "poly2") == 0)
	  return (3*x*x+6*x+4);
	else if(strcmp(funname, "imaginary") == 0)
	  return (3*x*x+6*x+4);
	else
	{
	  printf("Error: %s is not a valid function name\n", funname);
		exit(1);
	}
}
