#ifndef _BUTTON_H_
#define _BUTTON_H_

#define MESSAGE_BID 1122
typedef struct 
{
    long int messageNum;
    int keyInput;
    int pressed;
} BUTTON_MSG_T;

int buttonInit(void);
int buttonThfunc(void);
int buttonExit(void);
int probeButtonPath(char *newPath);
#endif
