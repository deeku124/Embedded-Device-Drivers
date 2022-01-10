#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
    int fd;
    char Ubuff[20]="def";
    char Kbuff[20];
    fd=open("/dev/cdevice",O_RDWR,0777);
    read(fd,Kbuff,sizeof(Kbuff));
    printf("data read is :%s\n",Kbuff);
    close(fd);
}