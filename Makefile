CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: libMyPeri.a fndtest

libMyPeri.a: fnd.o
	$(AR) rc libMyPeri.a fnd.o

fnd.o: fnd.h fnddrv.h fnd.c
	$(CC) fnd.c -o fnd.o -c

fndtest: fndtest.c fnd.h libMyPeri.a
	$(CC) fndtest.c -o fndtest -l MyPeri -L.
	scp fndtest ecube@192.168.0.9:/home/ecube
clean:
	rm *.o -rf
	rm *.a -rf
	rm fndtest -rf
