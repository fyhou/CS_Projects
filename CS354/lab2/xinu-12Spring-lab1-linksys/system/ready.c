/* ready.c - ready */

#include <xinu.h>

extern int ROUND_ROBIN; // defined in resched.c

qid16	readylist;			/* index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid,		/* ID of process to make ready	*/
	  bool8		resch		/* reschedule afterward?	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return(SYSERR);
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;

	if (ROUND_ROBIN == 0) 
		insert(pid, readylist, prptr->prprio);
	else
		insert(pid, readylist, 0);

	if (resch == RESCHED_YES) {
		resched();
	}
	return OK;
}
