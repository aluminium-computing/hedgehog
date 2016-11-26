/* Licensed under APL
   Copyright © 2013-2016 Aluminium Computing, Inc.
*/

#define HAS_LIBC FALSE
#define IS_KERNEL TRUE
#define X86_RING 0

#undef _GNU_SOURCE
#define _AIM_SOURCE
#define _HEDGEHOG
#define AIM_KERNEL
#define LICENSE AIM_PUBLIC

#include <hedgehog.h>

extern void HHClearScreen();
//extern void ____putch(char c);
extern void HHSetScreenColor(unsigned char forecolor, unsigned char backcolor);
extern void HHInitialiseVideo();

// VGA variables
unsigned short *textMemPtr;
 // 0, Black Background; 15, White Foreground
int attrib = (0 << 4) | (15 & 0x0F);
int csrX = 0;
int csrY = 0;

void HHCopyBuf(char *dest, char *src, int size) {
  int i = 0;
  while (i < size) {
    dest[i] = src[i];
	  i++;
  }
}

int HHStrCmp(char *a, char *b, int min) {
  int i = 0;
  while (i < min) {
    if (a[i] != b[i]) {
      return (-1);
    } else {
      i++;
    }
  }
  return 0;
}

len HHLenOf(char *string) {
  len i = 0;
  while (string[i] != '\0') {
    i++;
  }
  return i;
}




char HHGetCharFromPort(unsigned short _port) {
  char rv;
  __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
  return rv;
}

void HHSendCharToPort(unsigned short _port, char _char) {
  __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_char));
}


unsigned short *HHMemsetW(unsigned short *dest, unsigned short val, int count) {
    unsigned short *temp = (unsigned short *)dest;
    for( ; count != 0; count--) *temp++ = val;
    return dest;
}

void HHInitialiseVideo() /* British spelling */ {
  textMemPtr = (unsigned short *)0xB8000;
  HHClearScreen();
}


void HHScroll() {
  unsigned blank;
  unsigned screenLines = 25;
  blank = 0x20 | (attrib << 8);
  while(csrY >= screenLines)
   {
        HHCopyBuf((char *)textMemPtr, (char *)(textMemPtr + 80), (screenLines) * 80 * 2);
        HHMemsetW(textMemPtr + (screenLines - 1) * 80, blank, 80);
        csrY--;
    }
}

void HHMoveCsr() {
    unsigned temp;
    temp = csrY * 80 + csrX;
    HHSendCharToPort(0x3D4, 14);
    HHSendCharToPort(0x3D5, temp >> 8);
    HHSendCharToPort(0x3D4, 15);
    HHSendCharToPort(0x3D5, temp);
}

void HHClearScreen() {
  unsigned blank;
  int i;
  blank = 0x20 | (attrib << 8);
  for(i = 0; i < 25; i++)
    HHMemsetW(textMemPtr + i * 80, blank, 80);
  csrX = 0;
  csrY = 0;
  HHMoveCsr();
}
void HHPrintChar(char c) {
  unsigned short *where;
  unsigned att = attrib << 8;

    if(c == 0x08)
    {
        if(csrX != 0) csrX--;
    }

    else if(c == 0x09)
    {
        csrX = (csrX + 8) & ~(8 - 1);
    }
    else if(c == '\r')
    {
        csrX = 0;
    }

    else if(c == '\n')
    {
        csrX = 0;
        csrY++;
        HHScroll();
    }

    else if(c >= ' ')
    {
        where = textMemPtr + (csrY * 80 + csrX);
        *where = c | att;
        csrX++;
    }

    if(csrX >= 80)
    {
        csrX = 0;
        csrY++;
        HHScroll();
    }

    HHMoveCsr();
}

void HHPrint(char *foo) {
	int i = 0;
	while (foo[i] != '\0') {
		HHPrintChar(foo[i]);
		i++;
	}
}

void HHCrash(char *err) {
  attrib = (4 << 4) | (15 & 0x0F); // It's a RED screen of death
  HHClearScreen();
  int i;
  for (i=0;i <= 4;i++) {
    HHPrint("SYSTEM CRASH! ");
  }
  HHPrint("\n");
  HHPrint("Hedgehog has encountered an error: ");
  HHPrint(err);
  HHPrint("\n\n\nThis may have been caused by an bad program, or a hardware malfunction.\n");
  HHPrint("\nTry rebooting your computer.\n");
  HHPrint("\n\nFor more information, contact Aluminium Computing.\n");
  HHPrint("\nHedgehog v1.0");
	HHPrint("\n\nCopyright (c) 2013-2015 Aluminium Computing, Inc.\nYou may use it under the terms of the APL.\n");
	while (1) {
	}

}
int memBase = 0x100000;

int HHAlloc(size bytes) {
	if ((memBase + (int)bytes) > 0xFFFFFF) {
		attrib = (4 << 4) | (15 & 0x0F); /* Screen goes red to signify we're out of memory */
		HHPrint("ERROR: Out of memory!\n");
		HHPrint("Sorry, but Hedgehog ran out of memory. The system still works, so SAVE YOUR WORK IMMEDIATELY and restart.\n");
		HHPrint("\nTHE RUNNING PROGRAM MAY STOP WORKING AT ANY TIME!!!!\n");
		return NULL;
	}
	int retval = memBase;
	memBase += (int)bytes;
	return retval;
}

void HHFree(void *ptr) {
	#ifdef DEBUG
		HHPrint("HHFree() was called, but isn't yet implemented.\n");
	#endif /* DEBUG */
	#ifdef __GNUC__
		#warning "HHFree() is being called. It isn't implemented yet."
	#endif /* __GNUC__ */
	return;
}

char *HHStrCat(char *a, char *b, len max) { /*  http://linux.die.net/man/3/strncat helped me */
	len aLen = HHLenOf(a);
	int i;

	for (i = 0; i < max && b[i] != NULL; i++) {
		a[aLen +i] = b[i];
	}
	a[aLen + i] = NULL;

	return a;
}



char **HHStrTok(char *toTok, char delim) {
  len Len = HHLenOf(toTok);
  char **buf;
  int i = 0;
  int j = 0;
  int k = 0;
  while (i <= Len) {
    if (toTok[i] != delim) {
      buf[j][k] = toTok[i];
      i++; k++;
    } else { //first token done
      j++; i++;
      k = 0;
    }
  }
  return buf;
}

/*
void PrintChar(char char_) {
  ____putch(char_);
}
*/
// hedgehog() is usually called main()

void HHInit() {
  HHInitialiseVideo(); /* Note British spelling */
  #ifdef DEBUG
    HHPrint("Entered C Kernel\n");
  #endif//DEBUG
  HHPrint("Starting Up... 15%");
  HHGdtInstall();
	HHPrint(" 30%");
  HHIdtInstall();
	HHPrint(" 45%");
  HHIsrsInstall();
	HHPrint(" 60%");
  HHIrqInstall();
	HHPrint(" 70%");
  HHInstallKeyboard();
	HHPrint(" 85%");
  __asm__ __volatile__ ("sti");
	HHPrint(" 100%\n");
  HHPrint("Welcome to Hedgehog....\n\n\n");
  ShellMain();
  while (1) {
  }

}
