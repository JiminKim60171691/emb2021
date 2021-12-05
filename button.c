#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

// first read input device
#define INPUT_DEVICE_LIST	"/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"

int probeButtonPath(char *newPath)
{
	int returnValue = 0;
	int number = 0;
	FILE *fp = fopen(PROBE_FILE, "rt");
	while (feof(fp))
	{
		char tmpStr[200];
		fgets(tmpStr,200,fp);
		if(strcmp(tmpStr, HAVE_TO_FIND_1) == 0)
		{
			printf("YES! I found!: %s \r\n", tmpStr);
			returnValue = 1;
		}
		if( (returnValue == 1) && (strncasecmp(tmpStr, HAVE_TO_FIND_2, strlen(HAVE_TO_FIND_2)) == 0) )
		{
			printf("-->%s", tmpStr);
			printf("\t%c\r\n", tmpStr[strlen(tmpStr)-3]);
			number = tmpStr[strlen(tmpStr)-3] - '0';
			break;
		}
		fclose(fp);
		if(returnValue == 1)
		sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
		return returnValue;
	}
}

int buttonInit(void)
{
	int fp;
	int readSize, inputIdex;
	char inputDevpath[200] = {0,};
	struct input_event stEvent;

	if ( probeButtonPath(inputDevpath) == 0)
	{
		printf("ERROR! File Not Found!\r\n");
		printf("Did you insmod?\r\n");
		return 0;
	}
	printf("inputDevpath: %s\r\n", inputDevpath);
    fp = open (inputDevpath, O_RDONLY);
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
    return 1;
}

int buttonExit(void)
{
    close(fd);  
}


