//
// File descriptors
//

#include <cdefs.h>
#include <defs.h>
#include <file.h>
#include <fs.h>
#include <param.h>
#include <sleeplock.h>
#include <spinlock.h>
#include <proc.h>

struct devsw devsw[NDEV];
struct file_info file_table[NFILE];

int file_open(char* path, int mode) {

	struct inode* path_iptr = iopen(path);
	if (path_iptr == NULL) {
		return -1;
	}
	int file_table_idx = -1;

	for (int i = 0; i < NFILE; i++) {
		if (file_table[i].iptr == NULL) {
			file_table_idx = i;
			file_table[i].ref = 1;
			file_table[i].iptr = path_iptr;
			break;
		}
	}

	if (file_table_idx == -1) {
		return -1;
	}

	struct proc* p = myproc();
	int fd = -1;
	for (int i = 0; i < NOFILE; i++) {
		if (p->fd_array[i] == NULL) {
			fd = i;
			p -> fd_array[fd] = &file_table[file_table_idx];
			break;
		}
	}

	if (fd == -1) {
		return -1;
	}

	

	return fd;

}

int file_dup(int fd) {
	
	int free_fd = -1;
	for (int i = 0; i < NOFILE; i++) {
		if (myproc()->fd_array[i] == NULL) {
			free_fd = i;
			break;
		}
	}

	if (free_fd == -1) {
		return -1;
	}

	myproc()->fd_array[free_fd] = myproc()->fd_array[fd];

	return free_fd;

}

int str_cmp(char* str1, char* str2) {
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0') {
		if (str1[i] != str2[i]) {
			return 0;
		}
		i++;
	}

	return str1[i] == str2[i];
}