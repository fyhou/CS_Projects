/* lfflush.c  -  lfflush */

#include <xinu.h>

/*------------------------------------------------------------------------
 * lfflush  -  flush data block and index blocks for an open file
 *			(assumes file mutex is held)
 *------------------------------------------------------------------------
 */
status	lfflush (
	  struct lflcblk  *lfptr	/* ptr to file pseudo device	*/
	)
{
	if (lfptr->lfstate == LF_FREE) {
		return SYSERR;
	}

	/* Write data block if it has changed */

	if (lfptr->lfdbdirty) {
		write(Lf_data.lf_dskdev, lfptr->lfdblock, lfptr->lfdnum);
		lfptr->lfdbdirty = FALSE;
	}

	/* Write i-block if it has changed */

	if (lfptr->lfibdirty) {
		lfibput(Lf_data.lf_dskdev, lfptr->lfinum, &lfptr->lfiblock);
		lfptr->lfibdirty = FALSE;
	}
	
	return OK;
}
