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
    buzzerExit();
    return 0;
}