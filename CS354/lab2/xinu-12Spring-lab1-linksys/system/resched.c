/* resched.c - resched */

#include <xinu.h>

int ROUND_ROBIN = 1;  // value of 1 means FCFS is active, 0 is default algo

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* ptr to table entry for old process	*/
	struct procent *ptnew;	/* ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* process remains running */

		if (ROUND_ROBIN == 0) {
			if (ptold->prprio > firstkey(readylist)) {
				return;
			}
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;

		if (ROUND_ROBIN == 0)
			insert(currpid, readylist, ptold->prprio);
		else
			insert(currpid, readylist, 0);
	}

	/* Force context switch to highest priority ready process */

	currpid = dequeue(readylist);
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	preempt = QUANTUM;		/* reset time slice for process	*/
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr);

	/* Old process returns here when resumed */

	return;
}
