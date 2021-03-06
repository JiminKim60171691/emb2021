#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "textlcd.h"

#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

int main(void)
{
    textlcdInit();
    lcdtextwrite("  hello world!  ", "  game  start!  ", 1);
    sleep(1);
    lcdtextwrite("  hello world!  ", "  game  start!  ", 2);
    sleep(3);
    textlcdclear();
    sleep(1);
    lcdtextwrite("   Good  bye!   ", NULL, 1);
    sleep(1);
    textlcdExit();
    return 0;
}
