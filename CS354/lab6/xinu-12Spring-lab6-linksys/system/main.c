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
	int i; 
	did32 file = 0;

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

	for(i=0; i<Nlfl; i++){
		if(lfltab[i].lfstate == LF_USED){
			kprintf("Files open on this system, cannot format\r\n");
			return SYSERR;
		}
	}                        

	if(lfscreate(Lf_data.lf_dskdev, 100, 500*512) == SYSERR){
		kprintf("Creating the filesystem failed\r\n");
		return SYSERR;
	}

	/**
	 * CALL LS WITH NO FILES CREATED
	 */
	lflistdir(NULL);
	kprintf("\n\r");

	/**
	 * CREATE FOUR FILES
	 */
	file = open(LFILESYS, "I", "rw");
	if(file == SYSERR){
		kprintf("File open failed for /%d\r\n", i);
		return SYSERR;
	}

	file = open(LFILESYS, "LOVE", "rw");
	if(file == SYSERR){
		kprintf("File open failed for /%d\r\n", i);
		return SYSERR;
	}

	file = open(LFILESYS, "CS 354", "rw");
	if(file == SYSERR){
		kprintf("File open failed for /%d\r\n", i);
		return SYSERR;
	}

	file = open(LFILESYS, "LABS", "rw");
	if(file == SYSERR){
		kprintf("File open failed for /%d\r\n", i);
		return SYSERR;
	}

	/**
	 * CALL LS AGAIN
	 */
	lflistdir(4);

	return OK;
}
