CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: libMyPeri.a textlcdtest

libMyPeri.a: textlcd.o
	$(AR) rc libMyPeri.a textlcd.o

textlcd.o: textlcd.h textlcddrv.h textlcd.c
	$(CC) textlcd.c -o textlcd.o -c

textlcdtest: textlcdtest.c textlcd.h libMyPeri.a
	$(CC) textlcdtest.c -o textlcdtest -l MyPeri -L.
	scp textlcdtest ecube@192.168.0.9:/home/ecube
clean:
	rm *.o -rf
	rm *.a -rf
	rm textlcdtest -rf
