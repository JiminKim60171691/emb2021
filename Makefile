CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: libMyPeri.a buttontest

libMyPeri.a: button.o
	$(AR) rc libMyPeri.a button.o

button.o: button.h button.c
	$(CC) button.c -o button.o -c

buttontest: buttontest.c button.h libMyPeri.a
	$(CC) buttontest.c -o buttontest -l MyPeri -L. -lpthread
	scp -P30201 ledtest ecube@192.168.0.9:/home/ecube
clean:
	rm *.o -rf
	rm *.a -rf
	rm ledtest -rf
