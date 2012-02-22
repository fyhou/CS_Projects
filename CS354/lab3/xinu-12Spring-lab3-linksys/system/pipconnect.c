#include <xinu.h>

syscall pipconnect(int32 pip, pid32 end1, pid32 end2) {
				//( pipe    , reader    , writer    )

	intmask mask;
	struct pipe *pipeptr;

	mask = disable();

	if (isbadpipeid(pip) || (pipeptr = &pipelist[pip])->pipestate != PIPE_USED || (pipeptr = &pipelist[pip])->ownerPID != getpid() || !(isbadpid(end1)) || !(isbadpid(end2))) {
		if (!(isbadpid(end1)) kprintf("end1 is bad pid\n\r");
		if (!(isbadpid(end2)) kprintf("end2 is bad pid\n\r");
		
		restore(mask);
		return(SYSERR);
	}

	pipeptr = &pipelist[pip];
	pipeptr->pipestate = PIPE_CONNECTED;
	pipeptr->end1 = end1;
	pipeptr->end2 = end2;

	restore(mask);
	return(OK);
}
