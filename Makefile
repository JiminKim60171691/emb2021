CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: libMyPeri.a colorledtest

libMyPeri.a: colorled.o
	$(AR) rc libMyPeri.a colorled.o

colorled.o: colorled.h colorled.c
	$(CC) colorled.c -o colorled.o -c

colorledtest: colorledtest.c colorled.h libMyPeri.a
	$(CC) colorledtest.c -o colorledtest -l MyPeri -L.
	scp colorledtest ecube@192.168.0.9:/home/ecube
clean:
	rm *.o -rf
	rm *.a -rf
	rm colorledtest -rf