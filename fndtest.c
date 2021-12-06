#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnd.h"

#define FND_DRIVER_NAME		"/dev/perifnd"

int main(void)
{
	fndInit();
	int i = 500000;
	while(!(i<5))
	{
		fndDisp(i, 1);  // num 숫자 fnd에 띄우기 
		i = i/10;
		usleep(500000);
	}
	fndcounter(10);
	fndOff();

	return 0;
}
