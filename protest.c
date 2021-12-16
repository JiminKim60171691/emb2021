#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include <dirent.h>
#include <time.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "textlcddrv.h"
#include "textlcd.h"
#include "led.h"
#include "buzzer.h"
#include "button.h"
#include "colorled.h"
#include "fnd.h"
#include "bmpviewer.h"
#include "libfbdev.h"
#include "bitmapFileHeader.h"
#include "touch.h"

#define LED_DRIVER_NAME		"/dev/periled"
#define INPUT_DEVICE_LIST   "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"
#define MAX_SCALE_STEP 13
#define FND_DRIVER_NAME		"/dev/perifnd"
#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

#define COLOR_LED_DEV_R_ "/sys/class/pwm/pwmchip0/"
#define COLOR_LED_DEV_G_ "/sys/class/pwm/pwmchip1/"
#define COLOR_LED_DEV_B_ "/sys/class/pwm/pwmchip2/"

#define PWM_EXPORT "export"
#define PWM_UNEXPORT "unexport"
#define PWM_DUTY "pwm0/duty_cycle"
#define PWM_PERIOD "pwm0/period"
#define PWM_ENABLE "pwm0/enable"

#define PWM_COLOR_R 0
#define PWM_COLOR_G 1
#define PWM_COLOR_B 2

#define PWM_PERIOD_NS 1000000 //ns. = 1ms = 1khz

pthread_t tid[3];
int l=0;
int down=0;
static const int musicScale[MAX_SCALE_STEP] =
{
    262, /*do*/ 294,330,349,392,440,494, /* si */ 523, 329, 350, 245, 213, 262
};

void* doled (void*arg)
{
    while(1)
    {
        if(l==1) {ledLibwrong();}
        ledLibRand();
        usleep(200000);
        if(down==1)break;
    }
    
}

void* dobuzzer(void*arg)
{
    while (1)
    {
        printf("BGM1:the Canon\r\n");
        BGM1();
        if(down==1)break;
        sleep(1);
        printf("BGM2:Chopstick March\r\n");
        BGM2();
        if(down==1)break; 
        sleep(1);
         
    }
    
}

void* dofnd(void* arg)
{
    while(1)
    {fndcounter();
     if(down==1)break; 
    }
}
int main(void)
{
while(1)
{
    ledLibInit();
    buzzerInit();
    pwmLedInit();
    fndInit();
    touchInit();
    textlcdInit();
    int i,p=0;
    int select = 0;
    down=0;
    int msgID = msgget( MESSAGE_ID, IPC_CREAT|0666);
	TOUCH_MSG_T recvMsg;
    int err = 0;
    err = pthread_create(&(tid[0]),NULL,&doled, NULL);
    if (err !=0) printf("thread error!\r\n");
    err = pthread_create(&(tid[1]),NULL,&dobuzzer, NULL);
    if (err !=0) printf("thread error!\r\n");
    
    // 시작화면
    FrameBuffer_init();
    bmp_open("start.bmp"); 
    while(1)
    {
        msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
	    if(recvMsg.keyInput == 999)
	    {
	    	if (recvMsg.pressed == 1)
	    	{
	    		break;
	    	}
	    }
    }

    // 게임 고르기화면
    while(1)
    {
        FrameBuffer_init();
        bmp_open("select.bmp");  // 고르기 화면 띄우기
        lcdtextwrite("  hello world!  ", "  game  start!  ", 1);
        lcdtextwrite("  hello world!  ", "  game  start!  ", 2);  // textlcd 시작화면
        select = buttonInit(); // button으로 선택
        if(select == 1 | select == 2 | select == 3){ textlcdclear(); break; } 
    }
    err = pthread_create(&(tid[2]),NULL,&dofnd, NULL);
    if (err !=0) printf("thread error!\r\n");

    // 1번 게임 시작
    if(select == 1)
    {
        // 1번 게임 1번째 문제
        FrameBuffer_init();
        bmp_open("stage1.bmp");
        sleep(4);
        while (1)
	    {
            l=0;
            FrameBuffer_init();
            bmp_open("monkey.bmp");  // 1번 문제
		    msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		    //이떄는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
		    if(recvMsg.keyInput == 999)
		    {
				if (recvMsg.pressed == 1)
				{
			    	if (recvMsg.x >730)
			    	{
                        FrameBuffer_init();
                        bmp_open("monkey1.bmp");  // 1번 문제
                        Pwmanswer();
                        sleep(1);
			    		printf ("monkey answer!\r\n");
                        break;
			    	}
			    	else
				    {
                        FrameBuffer_init();
                        bmp_open("x.bmp");
				    	printf ("You touched anywhere... maybe center? :%d %d\r\n",recvMsg.x, recvMsg.y);
                        Pwmwrong();
                        l=1;
                        usleep(500000);
                        continue;
				    }
				    }
		    }
	    }
        // 1번 게임 2번째 문제
        FrameBuffer_init();
        bmp_open("stage2.bmp");
        sleep(4);
        while (1)
	    {
            l=0;
            FrameBuffer_init();
            bmp_open("cat.bmp");  // 1번 문제
		    msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		    //이떄는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
		    if(recvMsg.keyInput == 999)
		    {
				if (recvMsg.pressed == 1)
				{
			    	if (recvMsg.x <270 && recvMsg.y < 270)
			    	{
                        FrameBuffer_init();
                        bmp_open("cat1.bmp");  // 1번 문제
                        Pwmanswer();
                        sleep(1);
			    		printf ("cat answer!\r\n");
                        break;
			    	}
			    	else
				    {
                        FrameBuffer_init();
                        bmp_open("x.bmp");
				    	printf ("You touched anywhere... maybe center? :%d %d\r\n",recvMsg.x, recvMsg.y);
                        Pwmwrong();
                        l=1;
                        usleep(500000);
                        continue;
				    }
				    }
		    }
	    }

        // 1번 게임 3번째 문제
        FrameBuffer_init();
        bmp_open("stage3.bmp");
        sleep(4);
        while (1)
	    {
            l=0;
            FrameBuffer_init();
            bmp_open("dog.bmp");  // 1번 문제
		    msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		    //이때는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
		    if(recvMsg.keyInput == 999)
		    {
				if (recvMsg.pressed == 1)
				{
			    	if (recvMsg.x >730 && recvMsg.y < 270)
			    	{
                        FrameBuffer_init();
                        bmp_open("dog1.bmp");  // 1번 문제
                        Pwmanswer();
                        sleep(1);
			    		printf ("dog answer!\r\n");
                        break;
			    	}
			    	else
				    {
                        FrameBuffer_init();
                        bmp_open("x.bmp");
				    	printf ("You touched anywhere... maybe center? :%d %d\r\n",recvMsg.x, recvMsg.y);
                        Pwmwrong();
                        l=1;
                        usleep(500000);
                        continue;
				    }
				    }
		    }
	    }

        // 게임 시작,종료 선택
        FrameBuffer_init();
        bmp_open("congratulations.bmp");
        while(1)
        {
            msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
	        if(recvMsg.keyInput == 999)
	        {
	        	if (recvMsg.pressed == 1)
	        	{
                    if (recvMsg.x >550 && recvMsg.y < 300)
			    	{break;}
                    else
                    { p=1;break;}
	    	    }
	        }
        }
    }

    // 2번 게임 시작
    if(select == 2)
    {
        // 2-1
        while (1)
	    {
            l=0;
            FrameBuffer_init();
            bmp_open("milk.bmp");  // 1번 문제
		    msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		    //이떄는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
		    if(recvMsg.keyInput == 999)
		    {
				if (recvMsg.pressed == 1)
				{
			    	if ((300<recvMsg.x && recvMsg.x<600) && (100<recvMsg.y && recvMsg.y <170))
			    	{
                        FrameBuffer_init();
                        bmp_open("milk1.bmp");  // 1번 문제
                        Pwmanswer();
                        sleep(1);
			    		printf ("milk answer!\r\n");
                        break;
			    	}
			    	else
				    {
                        FrameBuffer_init();
                        bmp_open("x.bmp");
				    	printf ("You touched anywhere... maybe center? :%d %d\r\n",recvMsg.x, recvMsg.y);
                        Pwmwrong();
                        l=1;
                        usleep(500000);
                        continue;
				    }
				    }
		    }
	    }

        //2-2
        while (1)
	    {
            l=0;
            FrameBuffer_init();
            bmp_open("belt.bmp");  // 2번문제
		    msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		    //이떄는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
		    if(recvMsg.keyInput == 999)
		    {
				if (recvMsg.pressed == 1)
				{
			    	if ((300<recvMsg.x && recvMsg.x<600) && (290<recvMsg.y && recvMsg.y <360))
			    	{
                        FrameBuffer_init();
                        bmp_open("belt1.bmp");  // 1번 문제
                        Pwmanswer();
                        sleep(1);
			    		printf ("belt answer!\r\n");
                        break;
			    	}
			    	else
				    {
                        FrameBuffer_init();
                        bmp_open("x.bmp");
				    	printf ("You touched anywhere... maybe center? :%d %d\r\n",recvMsg.x, recvMsg.y);
                        Pwmwrong();
                        l=1;
                        usleep(500000);
                        continue;
				    }
				    }
		    }
	    }

        //2-3
        while (1)
	    {
            l=0;
            FrameBuffer_init();
            bmp_open("lee.bmp");  // 3번 문제
		    msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		    //이때는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
		    if(recvMsg.keyInput == 999)
		    {
				if (recvMsg.pressed == 1)
				{
			    	if ((300<recvMsg.x && recvMsg.x<600) && (220<recvMsg.y && recvMsg.y <290))
			    	{
                        FrameBuffer_init();
                        bmp_open("lee1.bmp");  // 1번 문제
                        Pwmanswer();
                        sleep(1);
			    		printf ("lee answer!\r\n");
                        break;
			    	}
			    	else
				    {
                        FrameBuffer_init();
                        bmp_open("x.bmp");
				    	printf ("You touched anywhere... maybe center? :%d %d\r\n",recvMsg.x, recvMsg.y);
                        Pwmwrong();
                        l=1;
                        usleep(500000);
                        continue;
				    }
				    }
		    }
	    }      

        // 게임 시작,종료 선택
        FrameBuffer_init();
        bmp_open("congratulations.bmp");
        while(1)
        {
            msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
	        if(recvMsg.keyInput == 999)
	        {
	        	if (recvMsg.pressed == 1)
	        	{
                    if (recvMsg.x >550 && recvMsg.y < 300)
			    	{break;}
                    else
                    { p=1;break;}
	    	    }
	        }
        } 
    }

    // 3번 게임 시작
    if(select == 3)
    {
        // 게임 1번째 문제
        FrameBuffer_init();
        bmp_open("stage4.bmp");
        sleep(4);
        while (1)
	    {
            l=0;
            FrameBuffer_init();
            bmp_open("medi.bmp");  // 1번 문제
		    msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		    //이떄는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
		    if(recvMsg.keyInput == 999)
		    {
				if (recvMsg.pressed == 1)
				{
                    FrameBuffer_init();
                    bmp_open("medi1.bmp");  // 1번 문제
                    Pwmanswer();
                    sleep(4);
		    		printf ("medi answer!\r\n");
                    break;   	
				}
		    }
	    }

        // 게임 2번째 문제
        FrameBuffer_init();
        bmp_open("stage5.bmp");
        sleep(5);
        while (1)
	    {
            l=0;
            FrameBuffer_init();
            bmp_open("updown.bmp");  // 1번 문제
		    msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		    //이떄는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
		    if(recvMsg.keyInput == 999)
		    {
				if (recvMsg.pressed == 1)
				{
                    FrameBuffer_init();
                    bmp_open("updown1.bmp");  // 1번 문제
                    Pwmanswer();
                    sleep(5);
		    		printf ("updown answer!\r\n");
                    break;   	
				}
		    }
		}
	    

        // 게임 3번째 문제
        FrameBuffer_init();
        bmp_open("stage6.bmp");
        sleep(4);
        while (1)
	    {
            l=0;
            FrameBuffer_init();
            bmp_open("AB.bmp");  // 1번 문제
		    msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
		    //이때는 터치가 일어나거나 아니면 터리가 끝날때만 여기에 들어옴!
		    if(recvMsg.keyInput == 999)
		    {
				if (recvMsg.pressed == 1)
				{
			    	FrameBuffer_init();
                    bmp_open("AB1.bmp");  // 1번 문제
                    Pwmanswer();
                    sleep(4);
		    		printf ("AB answer!\r\n");
                    break;
				}
		    }
	    }  

        // 게임 시작,종료 선택
        FrameBuffer_init();
        bmp_open("congratulations.bmp");
        while(1)
        {
            msgrcv(msgID, &recvMsg, sizeof (recvMsg)-sizeof (long int), 0, 0);
	        if(recvMsg.keyInput == 999)
	        {
	        	if (recvMsg.pressed == 1)
	        	{
                    if (recvMsg.x >550 && recvMsg.y < 300)
			    	{break;}
                    else
                    { p=1;break;}
	    	    }
	        }
        }
    }

    down=1;
    pthread_cancel(tid[0]);
    pthread_cancel(tid[1]);
    pthread_cancel(tid[2]);
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
    buzzerStopSong();
    ledLibExit();
    Pwmoff();
    pwmInactiveAll();
    buzzerExit();
    buttonExit();
    lcdtextwrite("   Good  bye!   ", NULL, 1);
    sleep(1);
    fndOff();
    textlcdExit();
    if(p==1){break;}
}

    return 0;
}