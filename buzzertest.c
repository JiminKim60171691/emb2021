#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

#define MAX_SCALE_STEP 18
static const int musicScale[MAX_SCALE_STEP] =
{
    392, 329, 350, 392, 329, 350, 392, 245,  213, 245, 262, 294, 330, 349, 330, 262, 294, 330, 175, 191, 223, 255, 223,191, 223 
};

int main(void)
{
    buzzerInit();

    /*for(int i = 0; i < 18; i++)
    {
        buzzerPlaySong(musicScale[i]); // 한 음씩 순서대로 출력
        printf("Current scale is: %d\r\n", musicScale[i]);
        usleep(300000);
    }*/

buzzerPlaySong(musicScale[0]);
usleep(300000);
buzzerPlaySong(musicScale[1]);
usleep(150000);
buzzerPlaySong(musicScale[2]);
usleep(150000);
buzzerPlaySong(musicScale[3]);
usleep(300000);
buzzerPlaySong(musicScale[4]);
usleep(150000);
buzzerPlaySong(musicScale[5]);
usleep(150000);
buzzerPlaySong(musicScale[6]);
usleep(150000);
buzzerPlaySong(musicScale[7]);
usleep(150000);
buzzerPlaySong(musicScale[8]);
usleep(150000);
buzzerPlaySong(musicScale[9]);
usleep(150000);
buzzerPlaySong(musicScale[10]);
usleep(150000);
buzzerPlaySong(musicScale[11]);
usleep(150000);
buzzerPlaySong(musicScale[12]);
usleep(150000);
buzzerPlaySong(musicScale[13]);
usleep(150000);
buzzerPlaySong(musicScale[14]);
usleep(300000);
buzzerPlaySong(musicScale[15]);
usleep(150000);
buzzerPlaySong(musicScale[16]);
usleep(150000);
buzzerPlaySong(musicScale[17]);
usleep(150000);


    buzzerStopSong(); // 부저 끄기
    printf("buzzer off\r\n");
    buzzerExit();
    return 0;
}
