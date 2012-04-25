#include <xinu.h>

syscall  lflistdir(
	  did32		descrp		/* descriptor for device	*/
	)
{
	intmask		mask;		/* saved interrupt mask		*/
	struct dentry	*devptr;	/* entry in device switch table	*/
	int32		retval;		/* value to return to caller	*/

	mask = disable();
	if (isbaddev(descrp)) {
		restore(mask);
		return SYSERR;
	}
  
	devptr = (struct dentry *) &devtab[descrp];
  
  if (devptr->dvnum == 4) {
    kprintf("fuck you\n\r");
  }
  else {
    kprintf("fuck you twice\n\r");
  }
  
	restore(mask);
	return retval;
}
