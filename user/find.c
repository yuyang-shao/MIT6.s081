/*
we should close fd when we don't use it because it's number is limited.
if we can't close , it may cause error in 61th line.
*/
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"


void 
find(char *path, char *target)
{
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;
    if((fd = open(path, O_RDONLY))<0){
        fprintf(2, "find: cannot open %s\n", path);
    }

    if(fstat(fd, &st) < 0){
        fprintf(2, "find1: cannot stat %s\n", path);
        close(fd);
        return;
    }

    strcpy(buf, path);
    p = buf+strlen(buf)-1;  //指向buf最后一个字符
    //找到最后一个/后面的文件名或目录名
    for(int i = strlen(buf)-1;i>=0;i--){
        if(*p=='/')
            break;
        p--;
    }
    p++;
    switch(st.type){
        case T_FILE:
            if(strcmp(p,target)==0)
                printf("%s\n",path);
            break;
        case T_DIR:
            if(strlen(path) + 1 + DIRSIZ +1 > sizeof(buf)){
                printf("find: path too long\n");
                break;
            }
        p = buf+strlen(buf);
        *p++ = '/';
        while (read(fd, &de, sizeof(de)) ==sizeof(de) )
        {
            if(de.inum == 0)
                continue;

            if(strcmp(de.name,".")==0||strcmp(de.name,"..")==0)
                continue;

            memmove(p, de.name,DIRSIZ);
            p[DIRSIZ] = 0;
            if(stat(buf, &st) < 0){
                printf("find2: cannot stat %s\n", buf);
                continue;
            }
            find(buf,target);    
        }    
    }
    close(fd);   //重要，fd有限，必须及时关闭，不然在第61行时将报错
}
int
main(int argc, char  *argv[])
{
    find(argv[1],argv[2]);
    exit(0);
}
