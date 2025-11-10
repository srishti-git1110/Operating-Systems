### Restricted ops
**Modes of execution:** Giving priviledges like opening a file, writing to it, modifying the disk etc. to any and every user process poses serious secruity risk and hence, every OS must be designed such that the user programs are restricted from doing it. The way to enable this is by having two modes of execution on the processor - the user mode and the kernel mode. Former is restricted in that it can't run just about any operation (eg. programs running in user mode cannot issue i/o requests) while code running in kernel mode has all the priviledges. Basically, the OS (which is nothing but a program) runs in kernel mode.

**System calls:** System calls are hence what enable user programs to issue requests for certain ops to be performed. Opening a file via open() is one such system call. While it looks like a normal procedure (function) call, it's different in that it's completion requires the CPU to execute instructions in kernel mode thus enabling the fulfillment of such restricted ops.

**How does it all happen?** 
By now, we know that the completion of a system call requires the processor to execute some code in kernel mode. The way it roughs happens is that as soon as a system call is made, the CPU does a few things:
- saves certain things like the program counter, the flags the program was run with, certain registers into the kernel stack. Kernel stack is a per-process memory allocated privately to the OS and is required to be able to circle back to the exact place where the program left execution in user mode.
- transitions into kernel mode ("traps into kernel mode") and utilizes the trap table to execute the said system call
- return-from-trap to enter back into the user mode while restoring the registers from the kernel stack to be able to continue program execution at the correct place in user mode.

(Read up on how the OS gains control once a process finishes execution.)

### Process Switching
The question here is: how is process switching possible when the OS (which is just another program) isn't running on the CPU? If the OS isn't running, it can't really do the anything. This is the "Regain" problem—how to make the OS regain control?

A timer interrupt (implemented at the hardware level as a physical device) interrupts the currently running processes every few ms and the control goes back to the OS that can then take the action its scheduler deems correct. 

Say if a process A is running and encounters an interrupt. Here's the steps that happen next:
1. The hardware saves the minimal necessary execution context (certain registers, program counter, flags etc.) in A's kernel stack.
2. The system traps into the kernel mode (OS regains control) and jumps to the interrupt handler code that is then executed. Note at the time of reboot, the OS tells the hardware which code to run to handle the interrupts.
3. If the scheduler (part of the OS and the handler code) now decides to execute a different process B (context switch as it's called), the switch() routine is called.
4. A's "full" execution context and its kernel stack pointer are read by the OS from the physical registers and saved to A's process structure (PCB in the memory).
5. B's full execution context is restored from its process structure (PCB that's in the memory again) into B's kernel stack. The OS also restores the execution context back onto the physical registers.
6. The current stack pointer is made to point to B's kernel stack and a return from trap is executed.
7. The hardware now restores the necessary user-state, pc, flags etc., from B's kernel stack (which the stack pointer is at) onto physical resources so that execution of B can next happen.
8. B's execution now starts in user mode using the program counter that was restored as one of the things.

### Extra notes
- The trap table, one that specifies what to do when a trap instruction is issue by a system call, is initialized at boot time by the OS. It cannot be modified by the user programs as that'd compromise the security by allowing the user programs to basically run whatever priviledge ops they want to.
- The interrupt handler is the same -- at boot time, the os must specify to the hardware what code to run when an interrupt occurs.
- While the OS is in charge of storing (and restoring) context from physical registers to the kernel stack and further to the PCB, the hardware is also responsible for the same only for a minimal set of context (the pc, flags, certain registers etc.) A question that I asked myself is that how could the CPU even do this without some software (OS/user program) asking it to do. Maybe a very naive question. The answer that I got is that this is possible via some built in logical circuitry on the CPU.