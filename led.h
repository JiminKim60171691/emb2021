#ifndef _LED_LIBRARY_H_
#define _LED_LIBRARY_H_

int ledLibInit(void);                     // 이 라이브러리는 led 켜기 전에 반드시 한번 불러야함
int ledLibOnOff(int ledNumber, int onOff);
// 이 함수는 ledNumber에 0~7을 넣으면, 그에 해당하는 led를 켜거나 끔
int ledLibStatus(void);
// 이 함수를 호출하려면 현재 led상태가 어떤지 확인해 준다, 만약 모든 led가 켜져 있으면 0xff를 리턴하고,
// 만약 모든 led가 껴져 있으면 0x00을 리턴한다.
// 만약 0xAA가 리턴되면, (10101010) => led는 4개만 켜져있는 것이다.
int ledLibExit(void);
// 이 함수를 호출하면 led를 전부 끄고 driver를 close한다.
int ledLibRaw(int ledstatus);
// 이 함수를 호출하면 ledStatus에 맞게 8개의 led를 전부 제어한다. 예를 들어 ledLibRaw(0x80); 1개만 켜진다.
int ledLibBlink(int ledNumber, int nth, int msec); 
// 1~8개의 led를 하나 골라서 n번깜빡이는데, 주기가 msec
int ledLibSeq(void);
// 왼쪽부터 순차적으로 led가 1초 간격으로 켜지는데 8개가 다 켜지면 모두 꺼진다.
int ledLibRand(void);
// 랜덤하게 led on/off
int ledLibwrong(void);
// 8개 led 켜졌다 꺼짐을 3번 반복