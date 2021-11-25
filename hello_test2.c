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

#define HELLO_DRIVER_NAME "/dev/hello1"

int main(int argc, char **argv)
{
    char array[2000]={0,};
    printf("입력하시오: ");
    scanf("%s", array);
    int fd;
    printf("enter test\n");


fd = open(HELLO_DRIVER_NAME, O_RDWR );
if(fd<0)
{
    printf("open fail\n");
    perror("driver(/dev/hello1) open error.\n");
    return 1;
}
printf("open success\n");

write(fd,&array,2000);
read(fd,array,2000);
printf("read value:%s\n",array);

int count;
printf("Nbyte 입력: ")
scanf("%d", &count);
unsigned int inputCmd =_IOR(0x55, 99, count);
unsigned long returnValue = ioctl(fd, inputCmd, count);
printf("Enter CMD\n");
close(fd);
return 0;
}
