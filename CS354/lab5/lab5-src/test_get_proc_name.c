#include <arch/x86/include/asm/unistd_64.h>
#include <stdio.h>
#include <errno.h> 

int main(int argc, char **argv) { 
        char buffer[32]; 
        if(argc < 2) 
                return 0; 
        int pid = atoi(argv[1]); 
        printf("Calling ...\n"); 
        syscall(__NR_my_get_proc_name_by_id, pid, buffer); 
        printf("proc name: %s\n", buffer); 
        return 0; 
}
