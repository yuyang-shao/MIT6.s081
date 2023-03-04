#include "kernel/types.h"
#include"user/user.h"

int fork1();
void panic(char*);

void
panic(char *s)
{
    fprintf(2,"%s\n",s);
    exit(1);
}

int 
fork1()
{
    int pid;

    pid = fork();
    if(pid == -1)
        panic("fork");
    return pid;
}

int
main(void)
{
    int p1[2];
    int p2[2];
    char a = 'a';
    if(pipe(p1)<0||pipe(p2)<0)
        panic("pipe");
    if(fork1()==0)
    {
        // close(0);
        // dup(p1[1]);
        close(p1[0]);
        read(p1[1],&a,sizeof(a));
        close(p1[1]);
        fprintf(1,"%d: received ping\n",getpid());
        // close(1);
        // dup(p2[0]);
        close(p2[1]);
        write(p2[0],&a,sizeof(a));
        close(p2[0]);
        exit(0);
    }
    // close(1);
    // int fd = dup(p[0]);
    close(p1[1]);
    write(p1[0],&a,sizeof(a));
    close(p1[0]);
    wait((int*)0);
    // close(0);
    // dup(p2[1]);
    close(p2[0]);
    read(p2[1],&a,sizeof(a));
    close(p2[1]);
    fprintf(1,"%d: received pong\n",getpid());
    exit(0);
    
}