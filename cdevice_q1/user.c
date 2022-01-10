#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>  
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>
int main()
{
int fd;

fd=open("/dev/MyCharDevice",O_RDWR,0777);
if(fd==0)
{
printf("error opening the driver program\n");
exit(1);
}

close(fd);
}