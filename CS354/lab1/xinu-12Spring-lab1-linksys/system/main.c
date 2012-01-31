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
	void goToBed(void);

	resume(create(goToBed, 1000, 20, "process 1", 0));
	resume(create(goToBed, 950, 20, "process 2", 0));

	pid32 i = 0;
	for (i = 0; i < NPROC-1; i++) {
		print_proc_info(i);
	}
	
	return OK;
}

void goToBed(void) 
{
	sleep(5000);
}
