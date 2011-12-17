/*********************************************************************
* Gaussian-Jordan Elimination with Partial Pivoting: Task 1 of Lab 3 *
* written by Joe Martella 					     *
* October 4, 2010						     *
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXROWS 100
#define MAXCOLS 101

void printMatrix(int rows, int columns, double **matrix);	 	// prints matrix
void swapRows(int rows, double **matrix);	 			// swaps rows

int row_to_swap = 0;
int column_number = 0;

/***********************************
* Main function takes in a matrix  *
* and solves for solutions using   *
* Gaussian-Jordan elimination with *
* Partial Pivoting. 		   *
* MF				   *
************************************/
int main(int argc, char  **argv) {
	char c = '0';		// helps me read input	
	int rows = 0;	 	// rows of matrix
	int  cols = 0; 		// columns of matrix
	int i, j; 		// incrementers
	double **matrix;	// matrix
	int cols_left = 0; 	// column elements left
	int element;		// read in elements of matrix

	///////////////////////////////
	// let us read some input in //
	///////////////////////////////
	if ((c = getchar()) != EOF) {
		rows = (int) c - '0';
		cols = rows + 1;
	}
	else {
		printf("Expected N (number of equations)\n");
		exit(1); 
	}

	//////////////////////////
	// allocate some memory //
	//////////////////////////
	if (!(matrix = (double **) malloc (rows*sizeof(double *)))){
		exit(1);
		}
	for (i = 0; i < rows+1; i++) {
		if (!(matrix[i] = (double *) malloc (cols*sizeof(double)))) {
		exit(1);
		}
	}

	////////////////////////
	// fill up the matrix //
	////////////////////////
	for (i = 0; i < rows; i++) {
		cols_left = cols;
		for (j = 0; j < cols; j++) {
			scanf("%d", &element);
			matrix[i][j] = (double) element;
			cols_left--;
			if ((c = getchar()) == '\n' || c == EOF)
				break;
		}
		if (cols_left > 0) {
			printf("Element a[%d][%d] is missing\n", i, j);
			exit(1);
		}
	}

	//////////////////////////////
	// print the initial matrix //
	//////////////////////////////
	printf("initial matrix\n");
	printMatrix (rows, cols, matrix);

	///////////////////////
	// solve the matrix //
	///////////////////////
	double divisor = 0;	// divisor
	double multiplier = 0;	// multiplier
	int k = 0;		// incrementer
	int m = 0; 		// incrementer

	for (i = 0; i < rows; i++) {
		swapRows (rows, matrix);
		printMatrix (rows, cols, matrix);
		printf("row %d /= %f\n", i, matrix[i][i]);
		divisor = matrix[i][i];
		for (j = 0; j < cols; j++) {
			matrix[i][j] = matrix[i][j] / divisor;
			if (matrix[i][j] == -0.000000)
				matrix[i][j] = 0.000000;
		}
		printMatrix (rows, cols, matrix);
		for (k = 0; k < rows; k++) {
			if (k != i) {
				multiplier = matrix[k][column_number];
				printf("row %d -= %f row %d\n", k, multiplier, i);
				for (m = 0; m < cols; m++) {
					matrix[k][m] = matrix[k][m] - multiplier*matrix[i][m];
				}
				printMatrix (rows, cols, matrix);
			}
		}
		column_number++;
	}

	for (i = 0; i < rows; i++) {
		printf("%f ", matrix[i][cols-1]);
	}
	printf("\n");

	//////////////////////////
	// give back the memory //
	//////////////////////////
	free (matrix);

	return 0;
}

/****************************************
* Prints a given 2d matrix      	*
* @param rows number of rows		*
* @param colums number of columns	*
* @param **matrix address of a 2d array *
* F1					*
*****************************************/
void printMatrix(int rows, int columns, double **matrix)
{
	int i = 0; 	// incrementer
	int j = 0; 	// incrementer

	printf("MATRIX:\n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < columns; j++) {
			printf("%f ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/*********************************************
* Swaps rows if the one above is greater     *
* @param rows number of rows		     *
* @param **matrix address of a 2d array      *
* F2					     *
**********************************************/
void swapRows(int rows, double **matrix) {
	int i = 0;	 		// incrementer
	int biggest_row = row_to_swap;	// stores biggest row number

	for (i = row_to_swap+1; i < rows; i++) {	
		if (fabs(matrix[biggest_row][column_number]) >= fabs(matrix[i][column_number])) {
		}
		else {
			biggest_row = i;
		}	
	}
	matrix[rows] = matrix[row_to_swap];
	matrix[row_to_swap] = matrix[biggest_row];
	matrix[biggest_row] = matrix[rows];
	
	if (matrix[row_to_swap][column_number] == 0) {
		printf("Error: Matrix is singular\n");
		exit(1);
	}

	printf("swapped %d and %d\n", row_to_swap, biggest_row); 
	
	row_to_swap++;
}
