CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: libMyPeri.a temptest
	
libMyPeri.a: temp.o
	$(AR) rc libMyPeri.a temp.o

temp.o: temp.h temp.c
	$(CC) temp.c -o temp.o -c

temptest: temptest.c temp.h libMyPeri.a
	$(CC) temptest.c -o temptest -l MyPeri -L.
	scp temptest ecube@192.168.0.9:/home/ecube/
clean:
	rm *.o -rf
	rm *.a -rf
	rm temptest -rf
