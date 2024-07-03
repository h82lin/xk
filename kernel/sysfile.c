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
  int fd, bytes_requested;
  char* buffer;

  if (argfd(0, &fd) == -1 || argint(2, &bytes_requested) == -1 || argptr(1, &buffer, bytes_requested)){
    return -1;
  }

  if (bytes_requested < 0) {
    return -1;
  }

  struct file_info* fi = myproc()->fd_array[fd];

  if (fi->permission == O_WRONLY) {
    return -1;
  }

  return file_read(fd, buffer, bytes_requested);

}

int sys_write(void) {
  // you have to change the code in this function.
  // Currently it supports printing one character to the screen.

  int n;
  char *p;

  if (argint(2, &n) < 0 || argptr(1, &p, n) < 0)
    return -1;
  



  int fd, bytes_write;
  char* buffer;

  if (argfd(0, &fd) == -1 || argint(2, &bytes_write) == -1 || bytes_write < 0 || argptr(1, &buffer, bytes_write)){
    return -1;
  }


  struct file_info* fi = myproc()->fd_array[fd];

  if (fi->permission == O_RDONLY) {
    return -1;
  }
  uartputc((int)(*buffer));

  return file_write(fd, buffer, bytes_write);
}

int sys_close(void) {

  int fd;
  if (argfd(0, &fd) == -1) {
    return -1;
  }
  file_close(fd);
  return 0;
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
