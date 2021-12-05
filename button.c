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
pthread_mutex_t lockinput;
static int fp;

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
	char inputDevpath[200] = {0,};
	BUTTON_MSG_T buttonRxData;
	if ( probeButtonPath(inputDevpath) == 0)
	{
		printf("ERROR! File Not Found!\r\n");
		printf("Did you insmod?\r\n");
		return 0;
	}

	printf("inputDevpath: %s\r\n", inputDevpath);
    fp = open (inputDevpath, O_RDONLY);

	if (pthread_mutex_init(&lockinput, NULL) != 0)  // 무택스 객체 초기화
	{
	printf ("\n Mutex Init Failed!!\n");
	return 1;
	}  // 초기화 실패하는 것을 출력으로 알려주는 if 문

	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
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
		int err = pthread_create(&buttonTh_id, NULL, buttonThfunc, NULL);
		if (err != 0)
		{
			printf("thread error!: [%d]\r\n", err);
			return -1;
		}
		msgrcv(msgID, &buttonRxData, sizeof(buttonRxData.keyInput),0,0);
		pthread_join(buttonTh_id, NULL);
	}
    return 1;
}

int buttonExit(void)
{
    close(fp);  
}

int buttonThfunc(void)
{
	int readSize, inputIndex;
	struct input_event stEvent;	
	BUTTON_MSG_T buttonTxData;

	int msgID = msgget ((key_t)MESSAGE_ID, IPC_CREAT|0666);
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

	pthread_mutex_lock(&lockinput);  // 쓰레드 lock
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
	    	case KEY_HOME: printf("Home key):"); break;
            case KEY_SEARCH: printf("Search key):"); break;
    	    case KEY_BACK: printf("Back key):"); break;
    	    case KEY_MENU: printf("Menu key):"); break;
            case KEY_VOLUMEDOWN: printf("Volume down key):"); break;
    	}
    	if(stEvent.value) printf("pressed\n");
    	else printf("released\n");
    }
	buttonTxData = stEvent;
	msgsnd(msgID, &buttonTxData, sizeof(buttonTxData.keyInput),0);
	pthread_mutex_unlock(&lockinput);   // 쓰레드 lock 풀어주기
    
}


