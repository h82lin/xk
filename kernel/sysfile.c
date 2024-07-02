//
// File-system system calls.
// Mostly argument checking, since we don't trust
// user code, and calls into file.c and fs.c.
//

#include <cdefs.h>
#include <defs.h>
#include <fcntl.h>
#include <file.h>
#include <fs.h>
#include <mmu.h>
#include <param.h>
#include <proc.h>
#include <sleeplock.h>
#include <spinlock.h>
#include <stat.h>

int sys_dup(void) {
  int fd;
  if (argfd(0, &fd) == -1) {
    return -1;
  }

  return file_dup(fd);
}

int sys_read(void) {
  // LAB1
  return -1;
}

int sys_write(void) {
  // you have to change the code in this function.
  // Currently it supports printing one character to the screen.

  int n;
  char *p;

  if (argint(2, &n) < 0 || argptr(1, &p, n) < 0)
    return -1;
  uartputc((int)(*p));
  return 1;
}

int sys_close(void) {
  // LAB1
  return -1;
}

int sys_fstat(void) {
  // LAB1
  return -1;
}

int sys_open(void) {

  char* file_name;
  int mode;
  if (argstr(0, &file_name) == -1 || argint(1, &mode) == -1) {
    return -1;
  }

  if (mode == O_CREATE  || (!str_cmp(file_name, "console") && (mode == O_WRONLY || mode == O_RDWR))) {
    return -1;
  }

  return file_open(file_name, mode);
 
}

int sys_exec(void) {
  // LAB2
  return -1;
}

int sys_pipe(void) {
  // LAB2
  return -1;
}

int sys_unlink(void) {
  // LAB 4
  return -1;
}
