#include "HRFS_driver.h"
HHFile GetFile(int device, char *path, char *name) {
	
}

void insert(HRFSFiles *head, HHFile *insertion) { /* inserts a file at the back of the linked list */
	HRFSFiles *newfile;
	newfile = (HRFSFiles *)HHAlloc(sizeof(HRFSFiles));
	if (newfile == -1) HHCrash("0x16_22_NOMEM");
	newfile->file = insertion;
	newfile->next = NULL;
	while (head->next != NULL) {
		head = head->next;
	} /* Now |head| = the last HHFile in the list! We are ready to insert. */
	head->next = newfile;
}