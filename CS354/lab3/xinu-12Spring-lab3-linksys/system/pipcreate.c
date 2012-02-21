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

		/* check table entry that corresponds to that ID */
		pipeptr = &pipelist[pipenum];
		if (pipeptr->pipestate == PIPE_FREE) {
			pipeptr->pipestate = PIPE_USED;
			pipeptr->psem = semcreate(256);
			pipeptr->csem = semcreate(0);
			pipeptr->ownerPID = getpid();
			pipeptr->pos  = 0;
			restore(mask);
			return(pipenum);
		}
	}

	restore(mask);
	return(SYSERR);
}
