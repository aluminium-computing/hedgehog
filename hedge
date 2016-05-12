/* Licensed under APL
   Copyright © 2013,2015 Aluminium Computing.
*/

#define HAS_LIBC FALSE
#define IS_KERNEL TRUE
#define X86_RING 0

#undef _GNU_SOURCE
#define _AIM_SOURCE
#define _HEDGEHOG

#ifndef HEDGE
#define HEDGE
#define VERSION "0.1"
void ShellMain();
char *input();
struct regs /* Registers */
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

typedef unsigned int size;
typedef long long big;
typedef unsigned long long ubig;//witous
typedef short len;
#ifndef NULL
	#define NULL 0
#endif
int HHAlloc(size bytes);
extern len HHLenOf(char *string);
extern void HHCopyBuf(char *dest, char *src, int size);
extern char HHGetCharFromPort(unsigned short _port);
extern void HHSendCharToPort(unsigned short _port, char _char);
extern void HHPrint(char *string);
extern void HHPrintChar(char c);
void HHCrash(char *err);
void irq_install_handler(int irq, void (*handler)(struct regs *r));

char *HHStrCat(char *a, char *b, len max);

extern void HHGdtSetGate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);

extern void HHGdtInstall();

extern void HHIdtInstall();
extern void HHIsrsInstall();

extern void HHIrqInstall();
extern void HHIrqInstallHandler();
extern void HHIrqUninstallHandler();
extern void HHInstallKeyboard();

#endif // HEDGE
