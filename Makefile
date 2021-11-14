all: final.elf

final.elf : main.c 1.o myProject.h
	gcc main.c -o final.elf

1.o: 1.c myProject.h
	gcc -c 1.c
clean:
	rm -rf *.o *.c *.elf