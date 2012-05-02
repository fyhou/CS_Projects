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
	
	int result;

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

          /************ EXAMPLE *****************/              
                        
          kprintf("Call 1\r\n");
	  result = lflistdir(Lf_data.lf_dskdev);
                        
	  file = open(LFILESYS, "ABC", "rw");
	  file = open(LFILESYS, "123", "rw");
	  file = open(LFILESYS, "DEF", "rw");
	  file = open(LFILESYS, "456", "rw");
	
	  close(file);
	  
          kprintf("Call 2\r\n");
	  result = lflistdir(Lf_data.lf_dskdev);
          kprintf("Call 3\r\n");
	  result = lflistdir(-1);
          kprintf("KillExpect");
	
	/************ EXAMPLE *****************/
	
	return OK;
}
