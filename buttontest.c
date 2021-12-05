#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#define INPUT_DEVICE_LIST   "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"

int main(int argc, char *argv[])
{
    int fp;
    int readSize, inputIndex;
    struct input_event stEvent;
    char inputDevPath[200]={0,};
    if(probeButtonPath(inputDevPath)==0)
    {
        printf("ERROR! File Not Found!\r\n");
        printf("Did you insmod?\r\n");
        return 0;
    }
    printf("inputDevPath: %s\r\n",inputDevPath);
    fp = open(inputDevPath, O_RDONLY);
    while(1)
    {
        readSize = read(fp, &stEvent, sizeof(stEvent));
        if(readSize != sizeof(stEvent))
        {
            continue;
        }
        if(stEvent.type == EV_KEY)
        {
            printf("EV_KEY)");
            switch(stEvent.code)
            {
                case KEY_VOLUMEUP: printf("Volume up key):"); break;
                case KEY_HOME: printf("Volume up key):"); break;
                case KEY_SEARCH: printf("Volume up key):"); break;
                case KEY_BACK: printf("Volume up key):"); break;
                case KEY_MENU: printf("Volume up key):"); break;
                case KEY_VOLUMEDOWN: printf("Volume up key):"); break;
            }
            if(stEvent.value) printf("pressed\n");
            else printf("released\n");
        }
        else
        ;
    }
    close(fp);
}