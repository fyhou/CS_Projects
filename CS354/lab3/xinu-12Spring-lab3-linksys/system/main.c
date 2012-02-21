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
	void pipeShit(int num);

	resume(create(pipeShit, 1000, 20, "piper", 1, 10));
	
	return OK;
}

void pipeShit (int num) 
{
	int i = 0;
	for (i = 0; i < num; i++)
	{
		int32 x = pipcreate();
		kprintf("Pipe %d created!\n\r", x);
	}

	pipdelete(3);
	int32 x = pipcreate();
	kprintf("Pipe %d created again!\n\r", x);
}

