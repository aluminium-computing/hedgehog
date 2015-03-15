#include "HRFS_driver.h"


void insert(HRFSFiles *head, HHFile *insertion) { /* inserts a file at the back of the linked list */
	HRFSFiles *newfile;
	newfile = (HRFSFiles *)HHAlloc(sizeof(HRFSFiles));
	if (newfile == NULL) HHCrash("0x16_22_NOMEM");
	newfile->file = insertion;
	newfile->next = NULL;
	while (head->next != NULL) {
		head = head->next;
	} /* Now |head| = the last HHFile in the list! We are ready to insert. */
	head->next = newfile;
}

char  **list(HRFSFiles *head) {
	char **buf = (char **)HHAlloc(511*260);
	int i=0;
	while (head->next != NULL && i < 512) {
		HHStrCat(buf[i], head->file->name, 505);/* the name */
		HHStrCat(buf[i], ".", 1);
		HHStrCat(buf[i], head->file->ext, 4);/* the extension */
		HHStrCat(buf[i], "\n", 1);
		i++;
	}
	return (char **)buf;
}