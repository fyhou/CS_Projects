#include <xinu.h>

syscall pipcreate() {
	intmask mask;          /* saved interrupt */
	int32 i;               /* counts all possible ports */
	int32 pipenum;         /* candidate pipe number to try */
	struct pipe *pipeptr;  /* pointer to pipe */

	mask = disable();

	for (i = 0; i < NPIPE; i++) {
		pipenum = pipenextid;
		if (++pipenextid >= NPIPE) {
			pipenextid = 0;
		}

		/* check tabl entry that corresponds to that ID */
		pipeptr = &pipelist[pipenum];
		if (pipeptr->pipestate == PIPE_FREE) {
			pipeptr->pipestate = PIPE_USED;
			pipeptr->ptssem = semcreate(PIPE_SIZE);
			pipeptr->ptrsem = semcreate(0);
			pipeptr->ownerPID = getpid();
			restore(mask);
			return(pipenum);
		}
	}

	restore(mask);
	return(SYSERR);
}
