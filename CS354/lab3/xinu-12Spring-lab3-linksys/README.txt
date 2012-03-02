Joseph Martella
CS 354 Lab 3
March 2, 2012

// System calls
- Each system call is implemented is working.

// Producer and consumer processes to test pipe functionality
- In main.c, the main function spawns a reader process, a writer process, and serves as the owner process itself.
- The owner process connects the reader and writer to a pipe that it creates.
- The writer process writes numbers 0 to 99 into the pipe buffer.
- The reader displays N (set to 10) numbers per iteration, then suspends itself.
- When the user presses ENTER, the reader is resumed and displays the next N lines.
- When the user enters 'q', the pipe is disconnected and deleted and the reader and writer are killed.

// Design decisions
- Straight forward implementation based on the spec.
- The buffer in the pipe is simply an array and I maintain writer and reader indexes to keep it synchronized
  and circular.
- All cases when an error should be returned (i.e. disconnected pipe, writer trying to read, etc.) is handled by
  returning SYSERR.

// Other notes
- Corner cases are handled, i.e. if owner disconnects or deletes pipe while writer or reader is waiting, it will
  be notified and exit gracefully.
- Extra credit is also taken care of.