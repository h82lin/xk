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
			file_table[i].permission = mode;
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

void file_close(int fd) {

	struct file_info* fi = myproc()->fd_array[fd];
	fi->ref -= 1;

	if (fi->ref == 0) {
		irelease(fi->iptr);
		fi->iptr = NULL;
		fi->offset = 0;
		fi->permission = 0;
	}
	myproc()->fd_array[fd] = NULL;

}

int file_read(int fd, char* buffer, int bytes_requested) {

	struct file_info* fi = myproc()->fd_array[fd];

	int bytes_read = concurrent_readi(fi->iptr, buffer, fi->offset, bytes_requested);

	if (bytes_read != -1) {
		
		fi->offset += bytes_read;
	}

	return bytes_read;

}

int file_write(int fd, char* buffer, int bytes_write) {

	struct file_info* fi = myproc()->fd_array[fd];

	int bytes_written = concurrent_writei(fi->iptr, buffer, fi->offset, bytes_written);

	if (bytes_written != -1) {
		
		fi->offset += bytes_written;
	}

	return bytes_written;
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