CC=i686-elf-gcc
SRC=/Users/acl/hedgehog
CFLAGS=-m32 -Wall -O  -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -DDEBUG -I$(SRC)/include
core:
	@echo "buiding core..."
	nasm -f elf -o out/hedgeboot.o core/hedgeboot.asm
	i686-elf-gcc $(CFLAGS) -DBUILD="1" -o out/hedgehog.o core/hedgehog.c
	i686-elf-gcc $(CFLAGS) -o out/kbd.o core/keyboard.c
kernel_stuff:
	# HedGDT
	nasm -f elf -o out/hedgdt_asm.o kernel_stuff/hedgdt.asm
	# Spike
	nasm -f elf -o out/spike_asm.o kernel_stuff/spike.asm
	# More HedGDT
	i686-elf-gcc $(CFLAGS)  -o out/hedgdt.o kernel_stuff/hedgdt.c
	# More Spike
	i686-elf-gcc $(CFLAGS)  -o out/spike.o kernel_stuff/spike.c
shell:
	i686-elf-gcc $(CFLAGS)  -o out/shell.o shell/shell.c
hedgehog:
	i686-elf-ld -melf_i386 -T link.ld -o out/hedgehog.bin out/hedgdt_asm.o out/hedgdt.o out/hedgeboot.o out/hedgehog.o out/kbd.o out/shell.o out/spike_asm.o out/spike.o

run:
	qemu-system-i386 -kernel out/hedgehog.bin

clean:
	rm -rf out/*
