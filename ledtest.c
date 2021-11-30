#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "led.h"



#define LED_DRIVER_NAME		"/dev/periled"



int main(void)
{
	ledLibInit();

    ledLibRaw(0xFF);
    sleep(1);
    ledLibRaw(0xAA);
    sleep(1);
    ledLibRaw(0x55);
    sleep(1);
    ledLibRaw(0x00);
    int i=0;
    for(i=0;i<8;i++)
     { 
        ledLibOnOff(i, 1);
        printf("0x%02X--ok?\n\r", ledLibStatus());
        sleep(1);
        ledLibOnOff(i, 0);
        sleep(1);
     }
    
    ledLiBlink(5, 10, 500); //5번 led 10번 깜빡 100ms 간격으로.

    ledLibSeq();
    sleep(1);

    ledLibRand();
    sleep(1);

    ledLibwrong(); 
    

    sleep(2);
	ledLibExit();
	return 0;
}
