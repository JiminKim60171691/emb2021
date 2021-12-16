CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: libMyPeri.a protest

libMyPeri.a: led.o button.o buzzer.o fnd.o colorled.o libfbdev.o touch.o textlcd.o
	$(AR) rc libMyPeri.a led.o button.o buzzer.o fnd.o colorled.o libfbdev.o touch.o textlcd.o

textlcd.o: textlcd.h textlcddrv.h textlcd.c
	$(CC) textlcd.c -o textlcd.o -c

touch.o: touch.c touch.h
	$(CC) touch.c -c -o touch.o

libfbdev.o: libfbdev.c libfbdev.h
	$(CC) libfbdev.c -o libfbdev.o -c

colorled.o: colorled.h colorled.c
	$(CC) colorled.c -o colorled.o -c

button.o: button.h button.c
	$(CC) button.c -o button.o -c

led.o: led.h led.c
	$(CC) led.c -o led.o -c

buzzer.o: buzzer.h buzzer.c
	$(CC) buzzer.c -o buzzer.o -c

fnd.o: fnd.h fnd.c
	$(CC) fnd.c -o fnd.o -c

protest: protest.c led.h button.h buzzer.h fnd.h colorled.h bmpviewer.h libMyPeri.a
	$(CC) -Xlinker --start-group protest.c -l MyPeri -Xlinker --end-group  -L. -o protest -lpthread
	scp protest ecube@192.168.0.6:/home/ecube
clean:
	rm *.o -rf
	rm *.a -rf
	rm protest -rf
