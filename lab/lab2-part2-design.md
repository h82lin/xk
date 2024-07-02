# Lab 2 Part 2 Design Doc: Pipe & Exec

## Instruction (Please Remove Upon Submission)
Follow the guidelines in [designdoc.md](designdoc.md).

This is a template for lab 2 part 2 design doc, you are welcomed to make adjustments, but  **you must answer the provided design questions**.

Once your design doc is finished, you should **submit it on Gradescope as a pdf**.
You can generate a pdf of this markdown file by running
```
pandoc -f markdown -o lab2-part2-dd.pdf lab/lab2-part2-design.md
```

## Overview

> Explain the motivation and the goal for Lab 2 Part 2. What do these system calls enable?

[ your text here ]

### Major Parts

> For each part below, explain the goals and key challenges to accomplishing these goals. 
> Please also explain how they interact with Lab 1 and Lab 2 part 1.
> For example, how does Pipe interact with file syscalls from Lab 1?

Pipe

- [ your text here ]

Exec

- [ your text here ]

Interactions

- [ your text here ]

<!-- for formatting, do not remove -->
\newpage
<!-- for formatting, do not remove -->

## In-depth Analysis and Implementation

### Pipe

**Functions To Implement & Modify**

> Example: implement `sys_pipe` from `kernel/sysfile.c`. 
> Implement `pipe_*` version of the lab 1 file operations (with details)

[ your text here ]

**Design Questions**

`pipe` returns 2 file descriptors: one for read end and one for write end. How many open files should be allocated as a result of `pipe` call? Can the read end and write end point to the same open file?

- [ your answer here ]

`pipe` creates a buffer backed by kernel memory that can be used for interprocess communication. Once a `pipe` is created, a process can invoke `read` with the read end. 
Just like reading a normal file, the read offsets advances upon each read. What metadata must a pipe track to support this?

- [ your answer here ]

Although we allow for partial reads, a read from an empty pipe should still block. What metadata must a pipe track to support this? 

- [ your answer here ]

Invoking `write` on a pipe write end should advance the write offset upon each write. What metadata must a pipe track to support this?

- [ your answer here ]

In addition, `write` on a pipe must be complete (all requested bytes must be written unless there are no more read ends). How does your design support write sizes larger than the size of your pipe buffer?

- [ your answer here ]

Lastly, `write` must be atomic (no interleaving writes). How do you ensure that a new writer cannot write until the current writer is done? What if the current writer is blocked?

- [ your answer here ]

The pipe buffer and its metadata should be allocated upon a `pipe` call. But when can it be deallocated? How are you tracking the life time of a pipe?

- [ your answer here ]

A writer may block when there's no room to write (given that there are still open read ends). But while the writer blocks, it is possible for all the readers to close. What happens 
if read ends are all closed while there are still blocking writers? How does your design avoid this situation?

- [ your answer here ]

The same is true for blocking readers. What happens if all write ends are closed while there are still blocking readers? How does your design avoid this situation?

- [ your answer here ]


**Corner Cases**

> Example: error checking for pipe allocation

[ your text here ]

**Test Plans**

[ your text here ]

<!-- for formatting, do not remove -->
\newpage
<!-- for formatting, do not remove -->


### Exec

**Functions To Implement & Modify**

> Example: Implement `sys_exec` in `kernel/sysexec.c`.

[ your text here ]


**Design Questions**

`exec` takes in a string path and a string array `argv`. How do you plan to validate the `argv` array? 

- [ your answer here ]

`exec` sets up a new address space for a process and frees the old address space. When is it safe to free the old address space?

- [ your answer here ]

When copying arguments onto the new stack, which address space is in use? Explain why.
 
- [ your answer here ]


**Corner Cases**

> Example: add padding before setting up the argv array because it must be word size aligned

[ your text here ]

**Test Plans** 

[ your text here ]


<!-- for formatting, do not remove -->
\newpage
<!-- for formatting, do not remove -->

## Risk Analysis

### Unanswered Questions

[ your text here ]

### Staging of Work

[ your text here ]

### Time Estimation

[ your text here ]
