#include <xinu.h>

syscall  lflistdir(
  did32		descrp		/* descriptor for device	*/
)
{
	intmask		mask;		/* saved interrupt mask		*/
	struct dentry	*devptr;	/* entry in device switch table	*/

	mask = disable();
	if (isbaddev(descrp)) {
		restore(mask);
		return SYSERR;
	}

	devptr = (struct dentry *) &devtab[descrp];

	if (devptr->dvnum == LFILESYS) {
		if (Lf_data.lf_dir.lfd_nfiles == 0) {
			kprintf("No files\n\r");
			restore(mask);
			return OK;
		}

		int i = 0;
		for (i = 0; i < LF_NUM_DIR_ENT; i++) { 	
			if (Lf_data.lf_dir.lfd_files[i].ld_ilist != NULL) {
				kprintf("%s\n\r", Lf_data.lf_dir.lfd_files[i].ld_name);
			}
		}
	}
	// if the device ain't quite right
	else {
		restore(mask);
		return SYSERR;
	}

	restore(mask);
	return OK;
}
