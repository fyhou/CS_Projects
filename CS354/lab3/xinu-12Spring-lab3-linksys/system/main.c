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
	void pipeTest(int num);
	void pipeDestroy(void);

	resume(create(pipeTest, 1000, 20, "test", 1, 10));
	//resume(create(pipeDestroy, 1000, 19, "destroy", 0));
	
	return OK;
}

void pipeTest (int num) 
{
	int i = 0;
	for (i = 0; i < num; i++)
	{
		int32 x = pipcreate();
		kprintf("Pipe %d created by process %d!\n\r", x, getpid());
	}

	int result = pipdelete(0);
	kprintf("pipdelete() result = %d\n\r", result);
}

void pipeDestroy(void) 
{
	int result = pipdelete(0);
	kprintf("pipdelete() result = %d\n\r", result);
}

