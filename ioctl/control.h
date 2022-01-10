#define magic 'D'


#define SET_BAUDRATE _IOWR(magic,0,int)

#define SET_NO_STOPBITS _IOWR(magic,1,int)

#define SET_DIRECTION_WRITE _IOW(magic,2,int)

#define SET_DEFAULTDATA _IOW(magic,3,int)