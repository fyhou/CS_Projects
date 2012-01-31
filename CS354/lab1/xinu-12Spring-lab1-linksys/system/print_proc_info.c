/* print_proc_info.c - print_proc_info */
 2
 3     #include < xinu.h >
 4     #include < string.h >
 5
 6     /*------------------------------------------------------------------------
 7     *  print_proc_info  -  Prints the info in proctab for a given pid
 8     *------------------------------------------------------------------------
 9     */
10     syscall print_proc_info(
11         pid32   pid   /* process ID     */
12     )
13     {
14     intmask mask;     /* saved interrupt mask   */
15
16           /*-----  Declare variables to hold values  ------*/
17           /*-----  ------------------------------- --------*/
18
19     mask = disable();
20
21           /*-----  Your code for fetching process specific info and displaying them goes here -----*/
22           /*-----  ------------------------------- --------*/
23           /*-----  ------------------------------- --------*/
24
25
26     restore(mask);
27
28     }
