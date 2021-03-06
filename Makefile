all:
	nasm -f elf32 kernel.asm -o kasm.o
	gcc -std=c99 -m32 -c kernel.c -o kc.o
	ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o

run:
	make . 
	qemu-system-i386 -kernel kernel

clean:
	rm kasm.o kc.o kernel
