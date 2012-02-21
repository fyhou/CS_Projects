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
	void test(int num);

	resume(create(test, 1000, 10, "process 2", 1, 11));
	
	return OK;
}

void test (int num) 
{
	int i = 0;
	for (i = 0; i < num; i++)
	{
		int32 x = pipcreate();
		kprintf("Pipe %d created!\n\r", x);
	}
}
