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
	
	char c;
	
	ready(end2, 1);
	ready(end1, 1); 

	while ((c = getc(stdin)) != 'q') 
	{
		if (c== '\n')
		{
			resume(end1);
		}
	}

	kprintf("User terminated program...\n\r");
	return OK;
}

void produce(void)
{
	kprintf("Producer is awake!\n\r");
	
	int i = 0;
	char buff[1];
	for (i = 0; i < 100; i++) 
	{
		buff[0] = i;
		int result = pipwrite(x, buff, 1);
		if (result == -1) kprintf("pipwrite error\r\n");
	}
}

void consume(void)
{
	kprintf("Consumer is awake!\n\r");
	
	char buff[15];
	while(1)
	{
		int i = 0;
		for (i = 0; i < N; i++) 
		{
			int result = pipread(x, buff, 15);
			if (result == -1) kprintf("pipread error\r\n");
			kprintf("%s", buff);
		}
		suspend(getpid());
	}
}
