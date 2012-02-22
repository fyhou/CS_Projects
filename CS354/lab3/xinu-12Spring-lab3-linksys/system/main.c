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
	void owner(pid32 end1, pid32 end2);
	void produce(void);
	void consume(void);

	//pid32 end1, end2;

	/*end2 = create(produce, 1000, 20, "producer", 0);  // writer
	end1 = create(consume, 1000, 20, "consumer", 0);  // reader
	
	x = pipcreate();
	pipconnect(x, end1, end2);

	resume(end2);
	resume(end1);*/
	
	char c;
	
	while (1 == 1) 
	{
		c = fgetc();
		kprintf("char = %c\n\r", c);
	}

	return OK;
}

void produce(void)
{
	while(1) 
	{
		int i = 0;
		for (i = 0; i < N; i++) 
		{
			
		}
	}
}

void consume(void)
{
	while(1)
	{
		;
	}
}
