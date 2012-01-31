/* print_proc_info.c - print_proc_info */

     #include <xinu.h>
     #include <string.h>

     /*------------------------------------------------------------------------
      *  print_proc_info  -  Prints the info in proctab for a given pid
      *------------------------------------------------------------------------
      */
     syscall print_proc_info(
         pid32   pid   /* process ID     */
     )
     {
     	intmask mask;     /* saved interrupt mask   */

        /*-----  Declare variables to hold values  ------*/
        /*-----  ------------------------------- --------*/
	  	char		*name;	    /* process name (for debugging)	*/
		pri16		priority;	/* process priority		*/
		uint32	ssize;		    /* stack size in bytes		*/
		char	*saddr;			/* stack address		*/

     	mask = disable();

        /*-----  Your code for fetching process specific info and displaying them goes here -----*/
        /*-----  ------------------------------- --------*/
        /*-----  ------------------------------- --------*/

		// get the process' table entry
		struct	procent *prptr;		/* ptr to process' table entry	*/
		prptr = &proctab[pid];

		if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		restore(mask);
		return SYSERR;
		}

		name     = prptr->prname;
		priority = prptr->prprio;
		ssize    = prptr->prstklen; 
		saddr    = prptr->prstkptr;
	
		kprintf("Process name: %s\n\r", name);
		kprintf("Process priority: %d\n\r", priority);
		kprintf("Process stack size: %d\n\r", ssize);
		kprintf("Process stack address: %x\n\r\n\r", saddr);

     	restore(mask);
		
		return OK;
     }
	
