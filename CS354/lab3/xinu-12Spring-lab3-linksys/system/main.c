/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

/************************************************************************/
/*																		*/
/* main - main program for testing Xinu									*/
/*																		*/
/************************************************************************/

int32 x = 0;     // pipe ID
int32 N = 10;    // amount of lines to show at a time

int main(int argc, char **argv)
{
	void produce(void);
	void consume(void);
	
	pid32 end1, end2;

	resume(end2 = create(produce, 1000, 20, "producer", 0));  // writer
	resume(end1 = create(consume, 1000, 20, "consumer", 0));  // reader
	
	x = pipcreate();
	int result = pipconnect(x, end1, end2);
	kprintf("Pipe connection resulted in: %d\n\r", result);
	
	char c;

	/*while ((c = getc(stdin)) != 'q') 
	{
		if (c== '\n')
		{
			resume(end1);
		}
	}*/

	kprintf("User terminated program...\n\r");
	return OK;
}

void produce(void)
{
	char buff[15] = "Hello, world!\n\r";
	while(1) 
	{
		pipwrite(x, buff, 15);
		kprintf("%s", buff);
	}
}

void consume(void)
{
	char buff[15];
	while(1)
	{
		int i = 0;
		for (i = 0; i < N; i++) 
		{
			pipread(x, buff, 15);
		}
		suspend(getpid());
	}
}
