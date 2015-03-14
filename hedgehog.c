/* Licensed under APL
   Copyright © 2013-2014 Aluminium Computing, Inc.
*/

#define HAS_LIBC FALSE
#define IS_KERNEL TRUE
#define X86_RING 0

#undef _GNU_SOURCE
#define _AIM_SOURCE
#define _HEDGEHOG
#define AIM_KERNEL
#define LICENSE AIM_PUBLIC

#include "hedge"

extern void HHClearScreen();
//extern void ____putch(char c);
extern void HHSetScreenColor(unsigned char forecolor, unsigned char backcolor);
extern void HHInitializeVideo();

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

void HHInitializeVideo() {
  textMemPtr = (unsigned short *)0xB8000;
  HHClearScreen();
}


void HHScroll() {
  unsigned blank, temp;
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
  HHPrint("Hedgehog has encountered an error: ");
  HHPrint(err);
  HHPrint("\n\n\nThis may have been caused by an bad program, or a hardware malfunction.\n");
  #ifdef DEBUG
	HHPrint("\nDid you type Control+;? That sequence may have caused this error");
  #endif // DEBUG
  HHPrint("\nTry rebooting your computer.\n");
  HHPrint("\n\nFor more information, visit aluminium.aimci in a Web browser, or contact\nAluminium Computing\n");
  HHPrint("\nHedgehog v1.0");
	HHPrint("\n\nCopyright (c) 2013-2014 Aluminium Computing, Inc.\nYou may use it under ther terms of the APL.\n");
	while (1) {
	}
  
}

/*
void PrintChar(char char_) {
  ____putch(char_);
}
*/
// hedgehog() is usually called main()

void HHInit() {
  HHInitializeVideo();
	#ifdef BUILD
		HHPrint("Hedgehog v1.0");
		HHPrint("\n\nCopyright (c) 2013-2014 Aluminium Computing, Inc.\nThis kernel is Open Software!\nYou may use it under ther terms of the APL.\n");
	#else
		HHPrint("Hedgehog v1.0 (UNKNOWN BUILD)\n\nCopyright (c) 2013-2014 Aluminium Computing, Inc.\nThis kernel is Open Software!\nYou may use it under ther terms of the APL.\n");
		HHPrint("WARNING: You are likely using a non-official build of Hedgehog.\n");
	#endif // BUILD
	#ifdef DEBUG
		HHPrint("WARNING: You are running a debug version of Hedgehog!\nYou MUST return this copy of Hedgehog to Aluminium Computing.\nIt may break at any time!!!\n\n");
	#endif // DEBUG
HHPrint("Booting...\n");
	HHPrint("Loading HedGDT...");
  HHGdtInstall(); 
	HHPrint(" 100%\n");
	HHPrint("Loading Spike...");
  HHIdtInstall();
	HHPrint(" 33%");
  HHIsrsInstall();
	HHPrint(" 66%");
  HHIrqInstall(); 
	HHPrint(" 100%\n");
	HHPrint("Enabling keyboard support...");
  HHInstallKeyboard();
	HHPrint(" 100%\n");
	HHPrint("Enabling Interrupts...");
  __asm__ __volatile__ ("sti"); 
	HHPrint(" 100%\n");
  HHPrint("Booting done!\n\n\n");
  
  while (1) {
  }
 
}

