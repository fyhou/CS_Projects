#include <stdio.h>
#include <stdlib.h>

int main () {
	char c;
	int count = 0;

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			count++;
		}
	}

	printf("Total lines: %d\n", count);
}
