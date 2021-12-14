CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: libMyPeri.a acceltest
	
libMyPeri.a: accel.o
	$(AR) rc libMyPeri.a accel.o

accel.o: accel.h accel.c
	$(CC) accel.c -o accel.o -c

acceltest: acceltest.c accel.h libMyPeri.a
	$(CC) acceltest.c -o acceltest -l MyPeri -L.
	scp acceltest ecube@192.168.0.9:/home/ecube/
clean:
	rm *.o -rf
	rm *.a -rf
	rm acceltest -rf
