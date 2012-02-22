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

	//char test[31] = "This problem is quite annoying.";
	char test[31] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam rhoncus porttitor nisi nec hendrerit. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Nunc sed neque tristique dui rhoncus interdum non id nulla. Morbi a orci sem, id eleifend elit. Nulla sed elit sit amet diam commodo mollis. Vestibulum scelerisque, est vitae sagittis viverra, ante arcu egestas lorem, sit amet euismod diam tortor a est. Integer ac pulvinar lectus. Donec pharetra auctor blandit. In hac habitasse platea dictumst. Vivamus vestibulum pharetra ipsum sit amet iaculis. Quisque vestibulum scelerisque pellentesque. Sed ornare, diam ac malesuada congue, elit orci lobortis est, non tristique ante mauris vitae purus.";
	result = pipwrite(x, test, 31);
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

