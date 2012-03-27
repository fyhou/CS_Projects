/* receiveb.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receiveb(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	struct	procent *sender;		/* ptr to process' table entry	*/
	umsg32	msg;			/* message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* block until message arrives	*/
	}
	msg = prptr->prmsg;		/* retrieve message		*/

	if (isempty(senderlist)) {
		prptr->prhasmsg = FALSE;	/* reset message flag		*/
	}
	else {
		pid32 senderPID = dequeue(senderlist);
		sender = &proctab[senderPID];
	
		prptr->prmsg = sender->sndmsg;
		prptr->prhasmsg = TRUE;

		sender->sndflag = FALSE;
		ready(senderPID, RESCHED_YES);
	}

	restore(mask);
	return msg;
}
