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
	char buf[50];

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
                        
	  file = open(LFILESYS, "ABC", "rw");
                if(file == SYSERR){
                        kprintf("File open failed for /%d\r\n", i);
                        return SYSERR;
                }
                
                if(write(file, "DEF\0", 4) == SYSERR){
                        kprintf("Write failed for /abcdef%d\r\n", i);
                        close(file);
                        return SYSERR;
                }
                seek(file, 0);
                if(read(file, buf, 4) == SYSERR){
                        kprintf("Read failed for /abcdef%d\r\n", i);
                        close(file);
                        return SYSERR;
                }
                
        kprintf("Read is %s\n",buf);
	
	close(file);
	
	/************ EXAMPLE *****************/
	
	return OK;
}
