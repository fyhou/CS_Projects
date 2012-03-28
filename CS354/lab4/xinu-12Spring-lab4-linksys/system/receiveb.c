
/* receive.c - receive */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receive  -  wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */
umsg32	receiveb(void)
{
	intmask	mask;			/* saved interrupt mask		*/
	struct	procent *prptr;		/* ptr to process' table entry	*/
	umsg32	msg;			/* message to return		*/

	mask = disable();
	prptr = &proctab[currpid];
	if (prptr->prhasmsg == FALSE) {
		prptr->prstate = PR_RECV;
		resched();		/* block until message arrives	*/
	}

	msg = prptr->prmsg;		/* retrieve message		*/
	prptr->prhasmsg = FALSE;	/* reset message flag		*/

	// check if any senders are waiting
	if (isempty(prptr->senderqueue)) {
		;
	}
	else {
		// get PID of sender that was waiting longest
		pid32 senderPID = dequeue(prptr->senderqueue);

		struct	procent *senderptr;
		senderptr = &proctab[senderPID];

		// get message and set appropriate flags
		prptr->prmsg = senderptr->sndmsg;
		prptr->prhasmsg = TRUE;
		senderptr->sndflag = FALSE;

		// reschedule sender
		ready(senderPID, RESCHED_YES);
	}

	restore(mask);
	return msg;
}
