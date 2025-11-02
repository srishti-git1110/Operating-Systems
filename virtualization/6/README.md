### Restricted ops
**Modes of execution:** Giving priviledges like opening a file, writing to it, modifying the disk etc. to any and every user process poses serious secruity risk and hence, every OS must be designed such that the user programs are restricted from doing it. The way to enable this is by having two modes of execution on the processor - the user mode and the kernel mode. Former is restricted in that it can't run just about any operation (eg. programs running in user mode cannot issue i/o requests) while code running in kernel mode has all the priviledges. Basically, the OS (which is nothing but a program) runs in kernel mode.

**System calls:** System calls are hence what enable user programs to issue requests for certain ops to be performed. Opening a file via open() is one such system call. While it looks like a normal procedure (function) call, it's different in that it's completion requires the CPU to execute instructions in kernel mode thus enabling the fulfillment of such restricted ops.

**How does it all happen?** 
By now, we know that the completion of a system call requires the processor to execute some code in kernel mode. The way it roughs happens is that as soon as a system call is made, the CPU does a few things:
- saves certain things like the program counter, the flags the program was run with, certain registers into the kernel stack. Kernel stack is a per-process memory allocated privately to the OS and is required to be able to circle back to the exact place where the program left execution in user mode.
- transitions into kernel mode ("traps into kernel mode") and utilizes the trap table to execute the said system call
- return-from-trap to enter back into the user mode while restoring the registers from the kernel stack to be able to continue program execution at the correct place in user mode.

### Process Switching
