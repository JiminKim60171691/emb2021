#ifndef _BUZZER_H_
#define _BUZZER_H_

int buzzerInit(void);           // buzzer 포함 함수
int buzzerPlaySong(int scale);  // buzzer on
int buzzerStopSong(void);       // buzzer off
int buzzerExit(void);           // buzzer exit
int BGM1(void); // 프로잭트 bgm 캐논변주곡
int BGM2(void); // 프로잭트 bgm 젓가락행진곡

#endif
