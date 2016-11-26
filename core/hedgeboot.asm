; Licensed under APL
; Copyright © 2013-2014 Aluminium Computing, Inc.

[BITS 32]
global start
start:
    mov esp, _stack     ; This points the stack to our new stack area
    jmp run

; This part MUST be 4byte aligned, so we solve that issue using 'ALIGN 4'
ALIGN 4
mboot:
    ; Multiboot macros to make a few lines later more readable
    MULTIBOOT_PAGE_ALIGN	equ 1<<0
    MULTIBOOT_MEMORY_INFO	equ 1<<1
    MULTIBOOT_AOUT_KLUDGE	equ 1<<16
    MULTIBOOT_HEADER_MAGIC	equ 0x1BADB002
    MULTIBOOT_HEADER_FLAGS	equ MULTIBOOT_PAGE_ALIGN | MULTIBOOT_MEMORY_INFO | MULTIBOOT_AOUT_KLUDGE
    MULTIBOOT_CHECKSUM	equ -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)
    EXTERN code, bss, end

    ; This is the GRUB Multiboot header. A boot signature
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd MULTIBOOT_CHECKSUM
    
    ; AOUT kludge - must be physical addresses. Make a note of these:
    ; The linker script fills in the data for these ones!
    dd mboot
    dd code
    dd bss
    dd end
    dd start

; This is an endless loop here. Make a note of this: Later on, we
; will insert an 'extern _main', followed by 'call _main', right
; before the 'jmp $'.
run:
  extern HHInit
  call HHInit
  jmp $

; Shortly we will add code for loading the GDT right here!


; In just a few pages in this tutorial, we will add our Interrupt
; Service Routines (ISRs) right here!



; Here is the definition of our BSS section. Right now, we'll use
; it just to store the stack. Remember that a stack actually grows
; downwards, so we declare the size of the data before declaring
; the identifier '_stack'
SECTION .bss
    resb 65536               ; This reserves 64KB of memory here
_stack:

