#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <unistd.h>
#include<asm/ioctl.h>
#include"control.h"

struct Defaultdata{
    int Baudrate;
    int stopbits;
    int parity;
};

int main()
{
    int fd,result,Baudrate=9600,stopbits=8;
    char Ubuff[50]="writing data....user";
    char Kbuff[50];
    struct Defaultdata Tosend={115200,1,0};
    fd=open("/dev/cdevice",O_RDWR,0777);
    if(fd<0)
    {
        printf("error opening device driver\n");
        return (-1);
    }
    result=ioctl(fd,SET_BAUDRATE,&Baudrate);
    if(result<0)
    {
        printf("ioctl error\n");
        return(-1);
    }
    ioctl(fd,SET_NO_STOPBITS,&stopbits);
    ioctl(fd,SET_DIRECTION_WRITE,NULL);
    ioctl(fd,SET_DEFAULTDATA,&Tosend);
    write(fd,Ubuff,sizeof(Ubuff));
    read(fd,Kbuff,sizeof(Kbuff));
    printf("%s\n",Kbuff);
    close(fd);
}