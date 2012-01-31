#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
	int i = 0;
	int j = 0;

	void * ptr1 = array;
	void * ptr2 = array;
	void * temp = malloc(elementSize);

	for (i = 0; i < n; i++) {
		for (j = i; j < n; j++) {
			if (ascending == 1) {
				if (compFunc(ptr1, ptr2) > 0) {	
					memcpy(temp,ptr1,elementSize);
					memcpy(ptr1,ptr2,elementSize);
					memcpy(ptr2,temp,elementSize);
				}
			}
			else {
				if (compFunc(ptr1, ptr2) < 0) {	
					memcpy(temp,ptr1,elementSize);
					memcpy(ptr1,ptr2,elementSize);
					memcpy(ptr2,temp,elementSize);
				}
			}	
			ptr2 = (void*) ((char*)array+j*elementSize);		
		}	
		ptr1 = (void*) ((char*)array+i*elementSize);
	}
}

