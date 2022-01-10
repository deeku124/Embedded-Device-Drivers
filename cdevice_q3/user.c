#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main()
{
    int fd;
    char Ubuff[50]="iam going to write programs cuz iam the user";
    char Kbuff[50];
    fd=open("/dev/cdevice",O_RDWR,0777);
    read(fd,Kbuff,sizeof(Kbuff));
    printf("reading data from the kernel\n");
    printf("%s",Kbuff);
    write(fd,Ubuff,sizeof(Ubuff));
    close(fd);
}