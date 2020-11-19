#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char** argv,char** environ)
{
    if(NULL==argv[1])
    {
        puts("Args are needed!\n");
        return 0;
    }
    if(NULL!=argv[3])
    {
        puts("Too many args\n");
        return 0;
    }
    int fd=open(argv[1],O_RDWR|O_CREAT,S_IRWXU);
    if(fd<0)
    {
        puts("no permission");
        return 0;
    }
    int fd2=open(argv[2],O_RDWR|O_CREAT|O_EXCL,S_IRWXU);
    if(fd2<0)
    {
        puts("file are exist,press y to recover");
        char ch;
        ch=getchar();
        if(ch == 'y')
        {
            fd2=open(argv[2],O_RDWR|O_CREAT,S_IRWXU);
            if(fd2<0)
            {
                puts("no permission");
                return 0;
            }
        }
        else
            return 0;
    }
    int count=1;
    for(int i=0;count>0;i++)
    {
        char buf;
        count=read(fd,&buf,sizeof(buf));
        write(fd2,&buf,sizeof(buf));
    }
    close(fd);
    close(fd2);
    return 0;
} 
