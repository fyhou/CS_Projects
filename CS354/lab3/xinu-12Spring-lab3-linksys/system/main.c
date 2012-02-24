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
	kill(getpid());
	
	char c;
	
	while (1) 
	{
		c = getchar();
		
		if (c == '\n') 
		{
			resume(end1);
		}
		else if (c == 'q')
		{
			pipdisconnect(x);
			pipdelete(x);
			
			kill(end1);
			kill(end2);
			
			kprintf("\n\rGoodbye.\n\r");
		
			break;
		}
	}

	return OK;
}

void produce(void)
{
	int i = 0;
	char buff[2];
	for (i = 0; i < 100; i++) 
	{
		if (i < 10) sprintf(buff, "0%d\n\r", i);
		else sprintf(buff, "%d\n\r", i);
		
		int result = pipwrite(x, buff, 2);
		if (result == -1) kprintf("pipwrite error\r\n");
	}
}

void consume(void)
{
	char buff[2];
	while(1)
	{
		int i = 0;
		for (i = 0; i < N; i++) 
		{
			int result = pipread(x, buff, 2);
			if (result == -1) kprintf("pipread error\r\n");
			kprintf("Read from pipe: %s\n\r", buff);
		}
		suspend(getpid());
	}
}
