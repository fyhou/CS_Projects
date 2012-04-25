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
    kprintf("there are %d files right now, nigga\n\r", Lf_data.lf_dir->lfd_nfiles);
  }
  // if the device ain't quite right
  else {
    return SYSERR;
  }
  
	restore(mask);
	return retval;
}
