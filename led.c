#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "led.h"

static int fd = 0;
static int ledStatus = 0;

int ledLibInit(void)
{
    fd = open (LED_DRV_NODE, O_RDWR);
    if(fd<0)
    {
        printf("Device Open Error!\r\n");
        exit(1);
    }
    ledStatus = 0;
    ledLibRaw(ledStatus);
    return 1;
}

int ledLibOnOff(int ledNumber, int onOff)//ledNumber에 0~7 넣으면, 그에 해당하는 led
{
    int lamp = 1;
    lamp = lamp << ledNumber;  // 00010000 해당 전구비트만 1임.
    ledStatus = (ledStatus &(~lamp)); //해당 전구비트만 0으로 바꿈.
    if (onOff)
      ledStatus = ledStatus | lamp;//해당 전구비트만 1로 바꾸고 나머지는 그대로.
    ledLibRaw(ledStatus);
    return 1;
}

int ledLibExit(void)
{
    ledLibRaw(0); //전부 끔.
    close(fd);  
}

int ledLibRaw(char ledwannabe) //ledStatus에 맞게 8개의 led 전부 제어. ex)ledLibRaw(0x80); 1개만 켜짐.
{
    if (fd>0)
    {
        write(fd, &ledwannabe, 1);


    }
    else
    {
        printf("WRONG! you must open device NODE!\r\n");
        exit(2);
    }
    ledStatus = ledwannabe;
    return 1;
    
}

int ledLibStatus(void)
{
  return ledStatus;
}

int ledLiBlink(int ledNumber, int nth, int msec)
{
    int i=0;
    for(i=0; i<nth; i++)
    {
        ledLibOnOff(ledNumber, 1); //on.
        usleep(1000*msec);
        ledLibOnOff(ledNumber, 0); //off.

    }

}

int ledLibSeq(void)
{
    sleep(1);
    for(int i=7;i>=0;i--){
        ledLibOnOff(i,1);
        sleep(1);
    }
    ledLibRaw(0); //전부 끔.
    return 1;
}

int ledLibRand(void)
{
    int i=0;
    i = rand()%256;
    ledLibRaw(i);
    return 1;
}

int ledLibwrong(void)
{
    for(int i=0;i<3;i++)
    {
        ledLibRaw(0xff);
        usleep(500000);
        ledLibRaw(0);
        usleep(200000);
    }
}
