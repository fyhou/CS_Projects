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
	int32	retval;

	/* Obtain network configuration from DHCP server */

	NetData.ipvalid = FALSE;
	retval = getlocalip();
	if (retval == SYSERR) 
		panic("Error: could not obtain an IP address\n\r");

	/* Open the remote disk */

	retval = open(RDISK,"XinuDisk","rw");
	if (retval == SYSERR)
		panic("Error: could not open the remote disk, check the server\n\r");

	kprintf("\n\r**********************************************************\n\r");

	/* Creating a shell process */

	resume(create(shell, 4096, 1, "shell", 1, CONSOLE));

	retval = recvclr();
	while (TRUE) {
		retval = receive();
		kprintf("\n\n\rMain process recreating shell\n\n\r");
		resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
	}

	return OK;
}
