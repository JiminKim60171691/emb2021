#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

#define MAX_SCALE_STEP 13

static const int musicScale[MAX_SCALE_STEP] =
{
    262, /*do*/ 294,330,349,392,440,494, /* si */ 523, 329, 350, 245, 213, 262
};

int main(void)
{
    buzzerInit();

    for(int i = 0; i < 8; i++)
    {
        buzzerPlaySong(musicScale[i]); // 한 음씩 순서대로 출력
        printf("Current scale is: %d\r\n", musicScale[i]);
        usleep(300000);
    }
    printf("BGM1:the Canon\r\n");
    BGM1();

    printf("BGM2:Chopstick March\r\n");
    BGM2();
    
    printf("buzzer off\r\n");
    buzzerExit();
    return 0;
}
