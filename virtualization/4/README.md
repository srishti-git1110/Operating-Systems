### Why is the separation between `exec()` and `fork()` needed?
While the goal is simply creating a new process (or more simply, running a new program), the design philosophy to separate `exec()` and `fork()` makes sense as it allows building pipelines where some additional code/setup needs to be done for the child process as a prep before it's actually run (via `exec()`). An example is output redirection via `>` like so,

```
wc p3.c > outputfile.txt
```

The output of `wc` when executed on `p3.c` gets saved in `outputfile.txt` rather than getting displayed on the terminal (standard output). Here is how the separation b/w `exec()` and `fork()` makes this possible: As soon as we run this command on shell*, a `fork()` call is made by the shell to spawn a child process. The file descriptor table of the child process is an inherited copy of the descriptor table of the parent which can look something this:

```
  FD 0 → /dev/tty  (stdin)
  FD 1 → /dev/tty  (stdout)
  FD 2 → /dev/tty  (stderr)
```

Now before calling exec() to run the actual command (the shell command), FD 1 in the child is made to point to a different file which in this case would be outputfile.txt, and the child descriptor table then looks like:

```
  FD 0 → /dev/tty  (stdin)
  FD 1 → outputfile.txt
  FD 2 → /dev/tty  (stderr)
```
And hence, once we run the given command via `exec()`, the output is redirected to outputfile.txt by virtue of the modified FD table. p4.c in this directory demonstrates this full thing. 

Think about a design philosophy where we had only one call for a new process creation - sort of like a unified version of `exec()` and `fork()`. Would redirection be possible with such a call? What about other features that are possbile via the current design?

*shell itself is a running program; and is the parent process in the light of our example! ;) Play around the following to see it in action:

```
ps -ef | grep bash
ps
```
