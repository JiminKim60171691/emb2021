#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

#define MAX_SCALE_STEP 13
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"

static const int musicScale[MAX_SCALE_STEP] =
{
    262, /*do*/ 294,330,349,392,440,494, /* si */ 523, 329, 350, 245, 213, 262, 110, 130, 173, 221
   // 0          1   2   3   4   5   6             7    8    9   10   11   12   13   14   15  16
};



static char gBuzzerBaseSysDir[128]; ///sys/bus/platform/devices/peribuzzer.XX 가 결정됨
static int fd_en, fd_freq;
static char path_en[200] = {0,}, path_freq[200] = {0,};

int findBuzzerSysPath(char *gBuzzerBaseSysDir)     //버저 경로 찾기: /sys/bus/platform/devices/peribuzzer.XX 의 XX를 결정하는 것
{
    DIR * dir_info = opendir(BUZZER_BASE_SYS_PATH);
    int ifNotFound = 1;
    if (dir_info != NULL)
    {
        while (1){
            struct dirent *dir_entry;   //XX 숫자 담을 변수
            dir_entry = readdir (dir_info);     //XX 숫자를 변수에 넣는다
            if (dir_entry == NULL) break;   //NULL값들어오면 break
            if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0)
            {
                ifNotFound = 0;
                sprintf(gBuzzerBaseSysDir,"%s%s/",BUZZER_BASE_SYS_PATH,dir_entry->d_name);
            }
        }
    }
    printf("find %s\n",gBuzzerBaseSysDir);
    return ifNotFound;
}

int buzzerInit(void)           // buzzer 포함 함수
{    
    if (findBuzzerSysPath(gBuzzerBaseSysDir) == 1)  //ifNotFound 트리거
    {
        printf("Failed. File Not EXIT\r\n");
        return 0;
    }
    sprintf(path_en, "%s%s", gBuzzerBaseSysDir, BUZZER_ENABLE_NAME);
    sprintf(path_freq, "%s%s", gBuzzerBaseSysDir, BUZZER_FREQUENCY_NAME);

    fd_en = open (path_en, O_WRONLY);
    fd_freq = open (path_freq, O_WRONLY);

    return 1;
}

int buzzerPlaySong(int scale)  // buzzer on
{
    dprintf(fd_freq, "%d", scale);
    write(fd_en, &"1", 1);
    
    return 1;
}

int buzzerStopSong(void)       // buzzer off
{
    write(fd_en, &"0", 1);

    return 1;
}

int buzzerExit(void)           // buzzer exit
{
    buzzerStopSong();
    close(fd_freq);
    close(fd_en);
    return 0;
}
int BGM1(void)
{
    buzzerPlaySong(musicScale[4]);
    usleep(300000);
    buzzerPlaySong(musicScale[8]);
    usleep(150000);
    buzzerPlaySong(musicScale[9]);
    usleep(150000);
    buzzerPlaySong(musicScale[4]);
    usleep(300000);
    buzzerPlaySong(musicScale[8]); 
    usleep(150000);  //5 392, 329, 350, 392, 329, //5

    buzzerPlaySong(musicScale[9]); 
    usleep(150000);
    buzzerPlaySong(musicScale[4]);
    usleep(150000);
    buzzerPlaySong(musicScale[10]);
    usleep(150000);
    buzzerPlaySong(musicScale[11]);
    usleep(150000);
    buzzerPlaySong(musicScale[10]); 
    usleep(150000); //10  350, 392, 245, 213, 245, //10

    buzzerPlaySong(musicScale[12]);
    usleep(150000);
    buzzerPlaySong(musicScale[1]);
    usleep(150000);
    buzzerPlaySong(musicScale[2]);
    usleep(150000);
    buzzerPlaySong(musicScale[3]); 
    usleep(150000);
    buzzerPlaySong(musicScale[2]); 
    usleep(300000); //15 262, 294, 330, 349, 330, //15

    buzzerPlaySong(musicScale[12]);
    usleep(150000);
    buzzerPlaySong(musicScale[1]);
    usleep(150000);
    buzzerPlaySong(musicScale[2]);
    usleep(300000);
    buzzerPlaySong(musicScale[13]);
    usleep(150000);
    buzzerPlaySong(musicScale[14]);
    usleep(150000); //20 262, 294, 330, 110, 130, //20

    buzzerPlaySong(musicScale[15]);
    usleep(150000);
    buzzerPlaySong(musicScale[16]);
    usleep(150000);
    buzzerPlaySong(musicScale[15]);
    usleep(150000);
    buzzerPlaySong(musicScale[14]);
    usleep(150000);
    buzzerPlaySong(musicScale[15]);
    usleep(150000); //25 173, 221, 173, 130, 173, //25

    buzzerPlaySong(musicScale[0]);
    usleep(150000);
    buzzerPlaySong(musicScale[10]);
    usleep(150000);
    buzzerPlaySong(musicScale[0]);
    usleep(150000);
    buzzerPlaySong(musicScale[16]);
    usleep(300000);
    buzzerPlaySong(musicScale[0]);
    usleep(150000); //30 262, 245, 262, 221, 262, //30

    buzzerPlaySong(musicScale[10]);
    usleep(150000);
    buzzerPlaySong(musicScale[16]);
    usleep(300000); 
    buzzerPlaySong(musicScale[15]);
    usleep(150000);
    buzzerPlaySong(musicScale[14]);
    usleep(150000);
    buzzerPlaySong(musicScale[15]);
    usleep(150000); //35 245, 221, 173, 130, 173, //35

    buzzerPlaySong(musicScale[14]);
    usleep(150000);
    buzzerPlaySong(musicScale[13]);
    usleep(150000);
    buzzerPlaySong(musicScale[14]);
    usleep(150000);
    buzzerPlaySong(musicScale[15]);
    usleep(150000);
    buzzerPlaySong(musicScale[16]);
    usleep(150000); //40 130, 110, 130, 173, 221, //40

    buzzerPlaySong(musicScale[10]);
    usleep(150000);
    buzzerPlaySong(musicScale[0]);
    usleep(150000);
    buzzerPlaySong(musicScale[16]);
    usleep(300000);
    buzzerPlaySong(musicScale[0]);
    usleep(300000);
    buzzerPlaySong(musicScale[10]);
    usleep(150000); //45 245, 262, 221, 262, 245, //45

    buzzerPlaySong(musicScale[0]);
    usleep(300000);
    buzzerPlaySong(musicScale[10]);
    usleep(300000);
    buzzerPlaySong(musicScale[0]);
    usleep(150000);
    buzzerPlaySong(musicScale[10]);
    usleep(150000);
    buzzerPlaySong(musicScale[16]);
    usleep(150000); //50 262, 245, 262, 245, 221, //50

    buzzerPlaySong(musicScale[10]);
    usleep(150000);
    buzzerPlaySong(musicScale[0]);
    usleep(150000);
    buzzerPlaySong(musicScale[1]);
    usleep(150000);
    buzzerPlaySong(musicScale[2]);
    usleep(300000);
    buzzerPlaySong(musicScale[3]);
    usleep(150000); //55 245, 262, 294, 330, 349, //55

    buzzerPlaySong(musicScale[4]);
    usleep(150000); 
    buzzerStopSong(); // 부저 끄기
}
int BGM2(void)
{
    int i = 0;
    for(i = 0; i < 12; i++)
    {
        buzzerPlaySong(musicScale[4]); // 솔 12번
        usleep(200000);
        buzzerStopSong();
        usleep(50000);
    }
    for(i = 0; i < 6; i++)
    {
        buzzerPlaySong(musicScale[6]); // 시 6번
        usleep(200000);
        buzzerStopSong();
        usleep(50000);
    }
    for(i = 0; i < 3; i++)
    {
        buzzerPlaySong(musicScale[7]); // 도 도 도
        usleep(200000);
        buzzerStopSong();
        usleep(50000);
    }
    buzzerPlaySong(musicScale[7]); // 도
    usleep(300000);
    buzzerPlaySong(musicScale[6]); // 시
    usleep(300000);
    buzzerPlaySong(musicScale[5]); // 라
    usleep(300000);
    for(i = 0; i < 12; i++)
    {
        buzzerPlaySong(musicScale[4]); // 솔 12번
        usleep(200000);
        buzzerStopSong();
        usleep(50000);
    }
    for(i = 0; i < 6; i++)
    {
        buzzerPlaySong(musicScale[6]); // 시 6번
        usleep(200000);
        buzzerStopSong();
        usleep(50000);
    }
    buzzerPlaySong(musicScale[7]); // 도
    usleep(300000);
    buzzerPlaySong(musicScale[4]); // 솔
    usleep(300000);
    buzzerPlaySong(musicScale[2]); // 미
    usleep(300000);
    buzzerPlaySong(musicScale[0]); // 도
    usleep(600000);
    buzzerStopSong(); // 부저 끄기
}