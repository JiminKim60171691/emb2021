#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"

#define INPUT_DEVICE_LIST   "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"

int main(void){

buttonInit();
buttonExit();
return 0;
}



