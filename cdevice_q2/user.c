#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd;
    char Ubuff[50]="hey this is user writing data into the driver";
    char Kbuff[50];
    fd=open("/dev/cdevice",O_RDWR,0777);
    if(fd==0)
    {
        printf("error opening device driver\n");
        exit(1);
    }
    printf("reading data from kernel\n");
    read(fd,Kbuff,sizeof(Kbuff));
    printf("%s",Kbuff);
    write(fd,Ubuff,sizeof(Ubuff));
    close(fd);
    
    
    
}