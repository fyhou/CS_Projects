Programming Assignment 4 (Intro to Threads) for CS 252

author: Joe Martella
date:   10/20/2011

*** My submission includes all the files given in the src folder, but my changes are saved in the files that were supposed to be changed. It was unclear to me whether or not to include all the files, but I did just in case. I thought this lab was very good - quite simple, but provided me with a great example and understanding of mutex and spin locks. ***

Part 1: Thread Creation
1.) The output obtained in step 3 is many occurrences of the characters A, B, and C and runs infinitely since the program is effectively in three infinite loops after the 2 threads are created and the main thread gets to printC. Because of context switches, A, B, and C are printed in different orders each time and at different frequencies. 

2.) The output of step 5 is all Cs. When this call: printC("C"); is made, the program enters an infinite loop in the printC function and never actually gets to the next 2 lines in the program which creates the other threads of execution. So the output is all Cs because the threads that would print A and B never come into existence. 

** In my code for step 4, I put the calls to create the two new threads above the printC("C"); so the threads that print D and E are actually created which is reflected in the output. **


Part 3: Spin Locks

										||   System (Kernel) Time	||	User Time	||	Real Time
pthread_mutex (count)				    ||			0.200 s			||	 9.328 s	||	 5.230 s
spin_lock (count_spin with thr_yield)   ||			0.960 s			||   2.711 s	||   1.972 s
spin_lock (count_spin without thr_yield ||			0.022 s         ||  11.286 s    ||   5.749 s

1.) User Time is the amount of CPU time spent in user-mode code within the process, aka actual CPU time used in executing the process. So there is such a drastic difference between count_spin without thr_yield and count_spin with thr_yield (8.575 s) because the CPU spends time busy waiting without thr_yield, adding to that User Time. However, when thr_yield is used, the thread gives up the CPU when it hits locked code, so no time is spent waiting in the process.

2.) System Time is the amount of CPU time spent in the kernel within the process, aka executing CPU time spent in system calls within the kernel. The reason why there is more time spent in count_spin with thr_yield in the kernel than count in the kernel (difference of 0.760 s) is because the thr_yield call executes a context switch to the privileged kernel mode (thus using CPU cycles to make the switch in kernel mode) where as count uses mutex locks that do not require the processes to use much time in kernel mode since the threads do not give up the CPU volunarily which means they do not have to make privileged kernel calls.

