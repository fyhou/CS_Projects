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
		pipe = &pipelist[pipenum];
		if (pipe->pipestate = PIPE_FREE {
			pipe->pipestate = PIPE_USED;
			pipe->ptssem = semcreate(PIPE_SIZE);
			pipe->ptrsem = semcreate(0);
			restore(mask);
			return(pipenum);
		}
	}

	restore(mask);
	return(SYSERR);
}
