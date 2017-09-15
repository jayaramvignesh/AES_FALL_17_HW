To create a system call, we need to basically do three steps.

Step 1: If we want to create a system call using SYS_DEFINE method. Then we can add our system 	  call under /kernel/sys.c

Step 2: Add the system call function declaration under /include/linux/syscalls.h . Add the declaration at the end of file just before #endif statement

Step 3: Finally we have to add the system call to the syscall table. This table is present in 
linux/arch/x86/entry/syscalls/syscall_64.tbl. Here add the system call at the end by giving the next number. If the current last system call is 335. Then the new system call number will be 336.

Finally build the kernel again and test it
