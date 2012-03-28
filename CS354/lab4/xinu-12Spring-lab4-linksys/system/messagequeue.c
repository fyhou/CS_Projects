#include <xinu.h>

umsg32 messageEnqueue (umsg32 msg, pid32 pid) {
	if (isbadpid(pid)) {
		return SYSERR;
	}

	struct	procent *prptr;		/* ptr to process' table entry	*/
	prptr = &proctab[pid];

	int messages = prptr->nummessages;
	prptr->msgqueue[messages] = msg;

	prptr->nummessages = messages + 1;

	return msg;	
}

umsg32 messageDequeue (pid32 pid) {
	if (isbadpid(pid)) {
		return SYSERR;
	}

	struct	procent *prptr;		/* ptr to process' table entry	*/
	prptr = &proctab[pid];

	umsg32 msg = prptr->msgqueue[0];
	int i = 0;

	for (i = 0; i < prptr->nummessages-1; i++) {
		prptr->msgqueue[i] = prptr->msgqueue[i+1];
	}

	prptr->nummessages = prptr->nummessages - 1;

	return msg;
}
