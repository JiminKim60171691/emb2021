all: final.elf

final.elf : main.c 1.o 2.o myProject.h
   gcc main.c -o final.elf
2.o: 2.c myProject.h
   gcc -c 2.c
1.o: 1.c myProject.h
   gcc -c 1.c
clean:
   rm -rf *.o *.c *.elf