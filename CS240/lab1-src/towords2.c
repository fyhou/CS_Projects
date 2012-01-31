#include <stdio.h>
#include <stdlib.h>

int main () {
	char c;
	int count = 0;
	int i = 0;

	while ((c = getchar()) != EOF) {
		if (i == 0) {
			printf("Word %d: %c", count, c);
			i++;
			if (count > 0)
				count++;
		}
		else if (c  == ' ') {
			count++;
			printf("\nWord %d: ", count);
		}
		else if (c == '\n') {
			i = 0;
			printf("\n");
			count++;
		}
		else
			printf("%c", c);
	}
	printf("Total words: %d\n", count);
}
