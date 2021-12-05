CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: libMyPeri.a buzzertest

libMyPeri.a: buzzer.o
	$(AR) rc libMyPeri.a buzzer.o

buzzer.o: buzzer.h buzzer.c
	$(CC) buzzer.c -o buzzer.o -c

buzzertest: buzzertest.c buzzer.h libMyPeri.a
	$(CC) buzzertest.c -o buzzertest -l MyPeri -L.
	scp buzzertest ecube@192.168.0.9:/home/ecube
clean:
	rm *.o -rf
	rm *.a -rf
	rm ledtest -rf
