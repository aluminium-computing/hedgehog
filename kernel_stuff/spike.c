// Adapted from www.osdever.net/bkerndev/Docs/idt.htm
// and www.osdever.net/bkerndev/Docs/isrs.htm

// Note: Spike is Hedgehog's interrupt system.


#define HAS_LIBC FALSE
#define IS_KERNEL TRUE
#define X86_RING 0

#undef _GNU_SOURCE
#define _AIM_SOURCE
#define _HEDGEHOG
#define AIM_KERNEL

#include <hedgehog.h>

/* These are function prototypes for all of the exception
*  handlers: The first 32 entries in the IDT are reserved
*  by Intel, and are designed to service exceptions! */
extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

/* These are own ISRs that point to our special IRQ handler
*  instead of the regular 'fault_handler' function */
extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void *irqRoutines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};


unsigned short *HHMemsetW(unsigned short *dest, unsigned short val, int count);

// IDT

struct idtEntry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idtPtr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idtEntry idt[256];
struct idtPtr idtp;

extern void idtLoad();

void HHIdtSetGate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;

}


void HHIdtInstall()
{
    idtp.limit = (sizeof (struct idtEntry) * 256) - 1;
    idtp.base = (unsigned int) &idt;
    HHMemsetW( (short unsigned int *) &idt, 0, sizeof(struct idtEntry) * 256);

    idtLoad();
}



void HHIsrsInstall()
{
    HHIdtSetGate(0, (unsigned)isr0, 0x08, 0x8E);
    HHIdtSetGate(1, (unsigned)isr1, 0x08, 0x8E);
    HHIdtSetGate(2, (unsigned)isr2, 0x08, 0x8E);
    HHIdtSetGate(3, (unsigned)isr3, 0x08, 0x8E);
    HHIdtSetGate(4, (unsigned)isr4, 0x08, 0x8E);
    HHIdtSetGate(5, (unsigned)isr5, 0x08, 0x8E);
    HHIdtSetGate(6, (unsigned)isr6, 0x08, 0x8E);
    HHIdtSetGate(7, (unsigned)isr7, 0x08, 0x8E);

    HHIdtSetGate(8, (unsigned)isr8, 0x08, 0x8E);
    HHIdtSetGate(9, (unsigned)isr9, 0x08, 0x8E);
    HHIdtSetGate(10, (unsigned)isr10, 0x08, 0x8E);
    HHIdtSetGate(11, (unsigned)isr11, 0x08, 0x8E);
    HHIdtSetGate(12, (unsigned)isr12, 0x08, 0x8E);
    HHIdtSetGate(13, (unsigned)isr13, 0x08, 0x8E);
    HHIdtSetGate(14, (unsigned)isr14, 0x08, 0x8E);
    HHIdtSetGate(15, (unsigned)isr15, 0x08, 0x8E);

    HHIdtSetGate(16, (unsigned)isr16, 0x08, 0x8E);
    HHIdtSetGate(17, (unsigned)isr17, 0x08, 0x8E);
    HHIdtSetGate(18, (unsigned)isr18, 0x08, 0x8E);
    HHIdtSetGate(19, (unsigned)isr19, 0x08, 0x8E);
    HHIdtSetGate(20, (unsigned)isr20, 0x08, 0x8E);
    HHIdtSetGate(21, (unsigned)isr21, 0x08, 0x8E);
    HHIdtSetGate(22, (unsigned)isr22, 0x08, 0x8E);
    HHIdtSetGate(23, (unsigned)isr23, 0x08, 0x8E);

    HHIdtSetGate(24, (unsigned)isr24, 0x08, 0x8E);
    HHIdtSetGate(25, (unsigned)isr25, 0x08, 0x8E);
    HHIdtSetGate(26, (unsigned)isr26, 0x08, 0x8E);
    HHIdtSetGate(27, (unsigned)isr27, 0x08, 0x8E);
    HHIdtSetGate(28, (unsigned)isr28, 0x08, 0x8E);
    HHIdtSetGate(29, (unsigned)isr29, 0x08, 0x8E);
    HHIdtSetGate(30, (unsigned)isr30, 0x08, 0x8E);
    HHIdtSetGate(31, (unsigned)isr31, 0x08, 0x8E);
}


char *exception_messages[] =
{
    "0x01_1_DIVZERO",
    "0x02_2_DEBUG",
    "0x03_3_NMI",
    "0x04_4_BRKPNT",
    "0x05_5_IDOVRF",
    "0x06_6_OUTBNDS",
    "0x07_7_IVOPCD",
    "0x08_8_NCOP",
    "0x09_9_DBFLT",
    "0x0A_10_CPSOV",
    "0x0B_11_BTSS",
    "0x0C_12_SEGNP",
    "0x0D_13_STKFLT",
    "0x0E_14_GPFLT",
    "0x0F_15_PGFLT",
    "0x10_16_UINT",
    "0x11_17_COPFLT",
    "0x12_18_ALCHK",
    "0x13_19_MAHCHK",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD",
    "0x14_20_RSRVD"
};




void fault_handler(struct regs *r)
{
    if (r->int_no < 32)
    {
        HHCrash(exception_messages[r->int_no]);
        while (1) {

        }
    }
}

/******* IRQ Handling ******/
/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irqRoutines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(int irq)
{
    irqRoutines[irq] = 0;
}

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void irq_remap(void)
{
    HHSendCharToPort(0x20, 0x11);
    HHSendCharToPort(0xA0, 0x11);
    HHSendCharToPort(0x21, 0x20);
    HHSendCharToPort(0xA1, 0x28);
    HHSendCharToPort(0x21, 0x04);
    HHSendCharToPort(0xA1, 0x02);
    HHSendCharToPort(0x21, 0x01);
    HHSendCharToPort(0xA1, 0x01);
    HHSendCharToPort(0x21, 0x0);
    HHSendCharToPort(0xA1, 0x0);
}

/* We first remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
void HHIrqInstall()
{
    irq_remap();

    HHIdtSetGate(32, (unsigned)irq0, 0x08, 0x8E);
    HHIdtSetGate(33, (unsigned)irq1, 0x08, 0x8E);
    HHIdtSetGate(34, (unsigned)irq2, 0x08, 0x8E);
    HHIdtSetGate(35, (unsigned)irq3, 0x08, 0x8E);
    HHIdtSetGate(36, (unsigned)irq4, 0x08, 0x8E);
    HHIdtSetGate(37, (unsigned)irq5, 0x08, 0x8E);
    HHIdtSetGate(38, (unsigned)irq6, 0x08, 0x8E);
    HHIdtSetGate(39, (unsigned)irq7, 0x08, 0x8E);
    HHIdtSetGate(40, (unsigned)irq8, 0x08, 0x8E);
    HHIdtSetGate(41, (unsigned)irq9, 0x08, 0x8E);
    HHIdtSetGate(42, (unsigned)irq10, 0x08, 0x8E);
    HHIdtSetGate(43, (unsigned)irq11, 0x08, 0x8E);
    HHIdtSetGate(44, (unsigned)irq12, 0x08, 0x8E);
    HHIdtSetGate(45, (unsigned)irq13, 0x08, 0x8E);
    HHIdtSetGate(46, (unsigned)irq14, 0x08, 0x8E);
    HHIdtSetGate(47, (unsigned)irq15, 0x08, 0x8E);
}

/* Each of the IRQ ISRs point to this function, rather than
*  the 'fault_handler' in 'isrs.c'. The IRQ Controllers need
*  to be told when you are done servicing them, so you need
*  to send them an "End of Interrupt" command (0x20). There
*  are two 8259 chips: The first exists at 0x20, the second
*  exists at 0xA0. If the second controller (an IRQ from 8 to
*  15) gets an interrupt, you need to acknowledge the
*  interrupt at BOTH controllers, otherwise, you only send
*  an EOI command to the first controller. If you don't send
*  an EOI, you won't raise any more IRQs */
void irq_handler(struct regs *r)
{
    /* This is a blank function pointer */
    void (*handler)(struct regs *r);

    /* Find out if we have a custom handler to run for this
    *  IRQ, and then finally, run it */
    handler = irqRoutines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if (r->int_no >= 40)
    {
        HHSendCharToPort(0xA0, 0x20);
    }

    /* In either case, we need to send an EOI to the master
    *  interrupt controller too */
    HHSendCharToPort(0x20, 0x20);
}
