hedgehog:
  # Hedgeboot
	nasm -f elf32 -o hedgeboot.o hedgeboot.asm
	# HedGDT
	nasm -f elf32 -o hedgdt_asm.o hedgdt.asm
	# Spike
	nasm -f elf32 -o spike_asm.o spike.asm
	
	# Main kernel (called by Hedgeboot)
	i686-elf-gcc -m32 -Wall -O  -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -DDEBUG  -DBUILD="1" -o hedgehog.o hedgehog.c
	# More HedGDT
	i686-elf-gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -DDEBUG  -o hedgdt.o hedgdt.c
	# More Spike
	i686-elf-gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -DDEBUG  -o spike.o spike.c
	# Keyboard
	i686-elf-gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -DDEBUG  -o kbd.o keyboard.c
	i686-elf-gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -DDEBUG  -o HRFS_driver.o HRFS_driver.c
	i686-elf-gcc -m32 -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -c -DDEBUG  -o fs.o fs.c
  # Link it all together 
	i686-elf-ld -melf_i386 -T link.ld -o hedgehog.bin hedgeboot.o hedgehog.o hedgdt.o hedgdt_asm.o spike_asm.o spike.o kbd.o HRFS_driver.o fs.o
	
run:
	kvm -kernel hedgehog.bin
