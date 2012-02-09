/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*									*/
/* main - main program for testing Xinu					*/
/*									*/
/************************************************************************/

int main(int argc, char **argv)
{
	void test(char c);

	resume(create(test, 1000, 20, "process 1", 1, 'J'));
	resume(create(test, 1000, 10, "process 2", 1, 'M'));
	
	return OK;
}

void test(char c) 
{
	int i = 0;
	while (i < 100) 
	{
		kprintf("%c\n\r", c);
		i++;

		if (i == 20 && c != 'X' && c != 'M')
			resume(create(test, 1000, 15, "process 3", 1, 'X'));
	}
}
