#ifndef __HRFS_DRIVER
#define __HRFS_DRIVER
#include "fs.h"
#include "hedge"
typedef struct HRFS_files {
	HHFile *file;
	struct HRFS_files *next;
} HRFSFiles;

#endif