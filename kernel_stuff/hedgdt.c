// From www.osdever.net/bkerndev/Docs/gdt.htm

// Note: HedGDT is Hedgehog's GDT.

#define HAS_LIBC FALSE
#define IS_KERNEL TRUE
#define X86_RING 0

#undef _GNU_SOURCE
#define _AIM_SOURCE
#define _HEDGEHOG
#define AIM_KERNEL

#include <hedgehog.h>

struct gdtEntry
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));

struct gdtPtr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));


struct gdtEntry gdt[3];
struct gdtPtr gp;

extern void HHGdtFlush();

void HHGdtSetGate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{

    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;


    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}
void HHGdtInstall()
{
    gp.limit = (sizeof(struct gdtEntry) * 3) - 1;
    gp.base = (unsigned int) &gdt;


    HHGdtSetGate(0, 0, 0, 0, 0);
    HHGdtSetGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    HHGdtSetGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);


    HHGdtFlush();
}
