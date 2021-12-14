#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

#include "temp.h"

int main(void)
{
    double temp;
    temp = read_temperature();
    
    printf("이것은 read_temperature 함수의 출력값(온도) : %lf \n", temp);
    return 0;
}
