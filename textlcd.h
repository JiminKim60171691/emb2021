#ifndef _TEXTLCD_H_
#define _TEXTLCD_H_

int textlcdInit(void); // 텍스트 LCD 초기화
int textlcdExit(void); // 텍스트 LCD 끄기
int textlcdclear(void); // 텍스트 LCD 화면 클리어
int lcdtextwrite(const char *str1, const char *str2, int lineFlag); // 텍스트 LCD 입력

#endif
