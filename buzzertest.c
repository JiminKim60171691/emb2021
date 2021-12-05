#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

#define MAX_SCALE_STEP 8
static const int musicScale[MAX_SCALE_STEP] =
{
    262, /*do*/ 294,330,349,392,440,494, /* si */ 523
};

int main(void)
{
    buzzerInit();
    int i = 0;
    for(i = 0; i < 12; i++)
    {
        buzzerPlaySong(musicScale[392]); // 솔 12번
        usleep(2500000);
        buzzerStopSong();
        usleep(500000);
    }
    for(i = 0; i < 6; i++)
    {
        buzzerPlaySong(musicScale[494]); // 시 6번
        usleep(2500000);
        buzzerStopSong();
        usleep(500000);
    }
    for(i = 0; i < 3; i++)
    {
        buzzerPlaySong(musicScale[523]); // 도 도 도
        usleep(2500000);
        buzzerStopSong();
        usleep(500000);
    }
    buzzerPlaySong(musicScale[523]); // 도
    usleep(3000000);
    buzzerPlaySong(musicScale[494]); // 시
    usleep(3000000);
    buzzerPlaySong(musicScale[440]); // 라
    usleep(3000000);
    for(i = 0; i < 12; i++)
    {
        buzzerPlaySong(musicScale[392]); // 솔 12번
        usleep(2500000);
        buzzerStopSong();
        usleep(500000);
    }
    for(i = 0; i < 6; i++)
    {
        buzzerPlaySong(musicScale[494]); // 시 6번
        usleep(2500000);
        buzzerStopSong();
        usleep(500000);
    }
    buzzerPlaySong(musicScale[523]); // 도
    usleep(3000000);
    buzzerPlaySong(musicScale[392]); // 솔
    usleep(3000000);
    buzzerPlaySong(musicScale[330]); // 미
    usleep(3000000);
    buzzerPlaySong(musicScale[262]); // 도
    usleep(6000000);
    buzzerStopSong(); // 부저 끄기
    buzzerExit();
    return 0;
}