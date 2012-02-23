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

	end2 = create(produce, 1000, 20, "producer", 0);  // writer
	end1 = create(consume, 1000, 20, "consumer", 0);  // reader
	
	x = pipcreate();
	int result = pipconnect(x, end1, end2);
	if (result == -1) kprintf("pipconnect error\n\r");
	
	ready(end2, 1);
	ready(end1, 1); 

	return OK;
}

void produce(void)
{
	int i = 0;
	char buff[4];
	for (i = 0; i < 100; i++) 
	{
		kprintf("i = %d\n\r", i);
		sprintf(buff, "%d\n\r", i);
		kprintf("buff = %s\n\r", buff);
		int result = pipwrite(x, buff, 4);
		if (result == -1) kprintf("pipwrite error\r\n");
	}
}

void consume(void)
{
	char buff[4];
	while(1)
	{
		int i = 0;
		for (i = 0; i < N; i++) 
		{
			int result = pipread(x, buff, 4);
			if (result == -1) kprintf("pipread error\r\n");
			kprintf("%s", buff);
		}
		//suspend(getpid());
	}
}
