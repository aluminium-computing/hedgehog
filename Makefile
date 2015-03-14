hedgehog:
  # Hedgeboot
	nasm -f elf32 -o hedgeboot.o hedgeboot.asm
	# HedGDT
	nasm -f elf32 -o hedgdt_asm.o hedgdt.asm
	# Spike
	nasm -f elf32 -o spike_asm.o spike.asm
	
	# Main kernel (called by Hedgeboot)
	gcc -m32 -Wall -O  -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -DDEBUG  -DBUILD="1" -o hedgehog.o hedgehog.c
	# More HedGDT
	gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -DDEBUG  -o hedgdt.o hedgdt.c
	# More Spike
	gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -DDEBUG  -o spike.o spike.c
	# Keyboard
	gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -DDEBUG  -o kbd.o keyboard.c
  # Link it all together 
	ld -melf_i386 -T link.ld -o hedgehog.bin hedgeboot.o hedgehog.o hedgdt.o hedgdt_asm.o spike_asm.o spike.o kbd.o
	
run:
	kvm -kernel hedgehog.bin
