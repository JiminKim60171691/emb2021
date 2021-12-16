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

pthread_t buttonTh_id;
static int fp;

int probeButtonPath(char *newPath)
{
	int returnValue = 0;
	int number = 0;
	FILE *fd = fopen(PROBE_FILE, "rt");
	while (!feof(fd))
	{
		char tmpStr[200];
		fgets(tmpStr,200,fd);
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
	}
		fclose(fd);
		if(returnValue == 1)
		sprintf(newPath, "%s%d", INPUT_DEVICE_LIST, number);
		return returnValue;
}

int buttonThfunc(void)
{
	int readSize, inputIndex;
	struct input_event stEvent;	
	BUTTON_MSG_T buttonTxData;
	buttonTxData.messageNum =0;
	buttonTxData.keyInput =0;
	buttonTxData.pressed =0;
	int msgID = msgget ((key_t)MESSAGE_BID, IPC_CREAT|0666);
	if(msgID == -1) 
	{ 
   		printf("msgID error!\r\n"); 
   		return -1; 
	}
   	int shmID = shmget((key_t)6017, 200, IPC_CREAT|0666);
   	if(shmID == -1) 
	{ 
   		printf("shmID error!\r\n"); 
   		return -1; 
	}
	char *shmemaddr;
	shmemaddr = shmat(shmID, (void*)NULL, 0);
	if( ((int)(shmemaddr) == -1) ) 
	{ 
   		printf("shmat error!\r\n"); 
   		return -2; 
	}      

	while (1)
	{
		readSize = read(fp, &stEvent, sizeof(stEvent));
 	   if(readSize != sizeof(stEvent))
   		{
	    	continue;
		}

		buttonTxData.messageNum = stEvent.type;
		buttonTxData.keyInput = stEvent.code;
		buttonTxData.pressed = stEvent.value;

		if(buttonTxData.messageNum == EV_KEY)
		{
			printf("EV_KEY)");
			switch(buttonTxData.keyInput)
			{
		    	case KEY_VOLUMEUP: printf("Volume up key):"); break;
				case KEY_HOME: printf("Home key):"); break;
   	    	 	case KEY_SEARCH: printf("Search key):"); break;
    	    	case KEY_BACK: printf("Back key):"); break;
	    		case KEY_MENU: printf("Menu key):"); break;
        		case KEY_VOLUMEDOWN: printf("Volume down key):"); break;
	    	}
    		if(buttonTxData.pressed) printf("pressed\n");
			else printf("released\n");
			msgsnd(msgID, &buttonTxData, sizeof(buttonTxData.keyInput),0);
			break;
		}

		
	}
    return 1;
}

int buttonInit(void)
{
	char inputDevpath[200] = {0,};
	BUTTON_MSG_T buttonRxData;
	buttonRxData.keyInput = 0;
	if ( probeButtonPath(inputDevpath) == 0)
	{
		printf("ERROR! File Not Found!\r\n");
		printf("Did you insmod?\r\n");
		return -1;
	}

	printf("inputDevpath: %s\r\n", inputDevpath);
    fp = open (inputDevpath, O_RDONLY);

	int msgID = msgget ((key_t)MESSAGE_BID, IPC_CREAT|0666);
	if(msgID == -1) 
	{ 
   		printf("msgID error!\r\n"); 
   		return -1; 
	}
   	int shmID = shmget((key_t)6017, 200, IPC_CREAT|0666);
   	if(shmID == -1) 
	{ 
   		printf("shmID error!\r\n"); 
   		return -1; 
	}
	char *shmemaddr;
	shmemaddr = shmat(shmID, (void*)NULL, 0);
	if( ((int)(shmemaddr) == -1) ) 
	{ 
   		printf("shmat error!\r\n"); 
   		return -2; 
	}      

	int err = pthread_create(&buttonTh_id, NULL, &buttonThfunc, NULL);
	if (err != 0)
	{
		printf("thread error!: [%d]\r\n", err);
		return -1;
	}
	while(1)
	{
		msgrcv(msgID, &buttonRxData, sizeof(buttonRxData.keyInput),0,0);
		shmdt(shmemaddr);
		if(buttonRxData.keyInput == KEY_HOME) {return 1;}
		else if(buttonRxData.keyInput == KEY_BACK) {return 2;}
		else if (buttonRxData.keyInput == KEY_SEARCH) {return 3;}
		else {return 0;}
	}
}

int buttonExit(void)
{
	pthread_join(buttonTh_id, NULL);
    close(fp);  
}



