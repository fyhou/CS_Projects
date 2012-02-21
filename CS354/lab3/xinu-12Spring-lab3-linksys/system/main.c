/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*																		*/
/* main - main program for testing Xinu									*/
/*																		*/
/************************************************************************/

int32 x = 11;

int main(int argc, char **argv)
{
	void pipeTest(pid32 end1, pid32 end2);
	void producerOrConsumer(int pORc);

	pid32 end1, end2;

	resume(end2 = create(producerOrConsumer, 1000, 20, "producer", 1, 1));
	resume(end1 = create(producerOrConsumer, 1000, 20, "consumer", 1, 0));
	resume(create(pipeTest, 1000, 19, "test", 2, end1, end2));

	return OK;
}

void pipeTest (pid32 end1, pid32 end2) 
{
	int num = 1;  // pipes to make
	int i = 0;    // iterator
	x = 11;       // pipe ID

	for (i = 0; i < num; i++)
	{
		x = pipcreate();
		kprintf("Pipe %d created by process %d!\n\r", x, getpid());
	}

	int result = pipconnect(x, end1, end2);
	kprintf("pipconnect() result = %d\n\r", result);

	char test[256] = "test";
	result = pipwrite(x, test, 256);
	kprintf("pipwrite() result = %d\n\r", result);
	
	char test2[2] = "fu";
	result = pipwrite(x, test2, 2);
	kprintf("pipwrite() result = %d\n\r", result);
}

void producerOrConsumer(int pORc)
{
	if (pORc)
	{
		return;
	}
	else 
	{
		return;
	}
}

