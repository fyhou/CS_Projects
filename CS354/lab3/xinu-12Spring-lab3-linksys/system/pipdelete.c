#include <xinu.h>

syscall pipdelete(int32 pip) {
	intmask mask;
	struct pipe *pipeptr;

	mask = disable();

	/* if pipe ID is bad or if that pipe is currently CONNECTED, return an ERROR */
	if (isbadpipeid(pip) || (pipeptr = &pipelist[pip])->pipestate == PIPE_CONNECTED || (pipeptr = &pipelist[pip])->ownerPID != getpid()) {
		restore(mask);
		return(SYSERR);
	}

	/* free up the pipe */
	pipeptr = &pipelist[pip];
	pipeptr->pipestate = PIPE_FREE;
	semreset(pipeptr->ptssem, PIPE_SIZE);
	semreset(pipeptr->ptrsem, 0);
		

	/* set next available to the one just freed and return */
	pipenextid = pip;
	restore(mask);
	return(OK);
}
