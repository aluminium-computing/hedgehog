#ifndef __FS_H
#define __FS_H

typedef struct file_struct {
	char name[255]; // eg 'test'
	void **data /* data */;
	char ext[4]; // eg 'txt'
	int perms; /* eg 2 */ //1=r/o 2=r/w 3=r/x 4=r/w/x
} HHFile;

#endif
