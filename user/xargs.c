#include"kernel/types.h"
#include "user/user.h"
#include"kernel/param.h"
#include "kernel/fcntl.h"


void
xargs(int argc,char ** argv)
{
    
    static char buf[100]; 
    char * sargv[MAXARG];//表示从标准输入中读取的参数
    int i = 0;
    int count = 0;
    while(read(0,&buf[i],sizeof(char))!=0)
    {
        if(buf[i]=='\n')
        {
            buf[i] = '\0';//表示一个参数结尾
            if(read(0,&buf[++i],sizeof(char))!=0)
                sargv[++count] = &buf[i];
        }
        i++;
    }
    sargv[0] = &buf[0];

    for(int i = 0;i < argc - 1;i++)
    {
        *(argv + i) = *(argv + i +1);
    }
    

    for (int i = 0; i <= count; i++)
    {
        * (argv + argc -1) = sargv[i];
        if(fork()==0)
        {
            exec(argv[0],argv);
        }   
    }
    wait((int*)0); 
}

int
main(int argc,char *argv[])
{
    xargs(argc,argv);
    exit(0);
}