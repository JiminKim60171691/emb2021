#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"

#define MAX_SCALE_STEP 32
static const int musicScale[MAX_SCALE_STEP] =
{
    392, 329, 350, 392, 329, 350, 392, 245,  213, 245, 262, 294, 330, 349, 330, 262, 294, 330, 110, 130, 173, 221, 173, 130,  173 ,   262, 245, 262, 221, 262, 245, 221, 173, 130, 173, 130,110 ,130, 173 , 221, 245, 262, 221, 262,245,262, 245,262,245,
   //솔.  미   파   솔.  미   파   솔    시    라   시    도   레    미  파    미    도  레    미.   미   파   솔    라   솔    파    솔      도    시   도  라.  도   시    라.  솔    파   솔  파    미  파    솔    라   시   도    라.   도  시   도.   시  도   시  라   시  도   레 미 파
    221,245,262,294,330,349,392
};//라   시  도  레   미  파 솔

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
usleep(300000);
buzzerPlaySong(musicScale[18]);
usleep(150000);
buzzerPlaySong(musicScale[19]);
usleep(150000);
buzzerPlaySong(musicScale[20]);
usleep(150000);
buzzerPlaySong(musicScale[21]);
usleep(150000);
buzzerPlaySong(musicScale[22]);
usleep(150000);
buzzerPlaySong(musicScale[23]);
usleep(150000);
buzzerPlaySong(musicScale[24]);
usleep(150000);
buzzerPlaySong(musicScale[25]);
usleep(150000);
buzzerPlaySong(musicScale[26]);
usleep(150000);
buzzerPlaySong(musicScale[27]);
usleep(150000);
buzzerPlaySong(musicScale[28]);
usleep(300000);
buzzerPlaySong(musicScale[29]);
usleep(150000);
buzzerPlaySong(musicScale[30]);
usleep(150000);
buzzerPlaySong(musicScale[31]);
usleep(300000);

    buzzerStopSong(); // 부저 끄기
    printf("buzzer off\r\n");
    buzzerExit();
    return 0;
}
