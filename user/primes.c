#include "kernel/types.h"
#include "user/user.h"
#define MAXSIZE 35
// typedef struct figure{
//     int num; //数字
//     int flag; //标志是否被筛掉
// }figure;
void 
primeSieve(int a[],int length)
{
    if(length==0){
        return;
    }
    int p[2];
    pipe(p);
    int count = 0;//本轮筛进下一轮的个数
    // close(0);
    fprintf(1,"primer %d\n",a[0]);


    for(int i = 1;i<length;i++)
    {
        if(a[i]%a[0]!=0){
            count++;
            // fprintf(p[0],"%d",a[i]);
            write(p[1],&a[i],sizeof(a[i]));
        }
    }
    close(p[1]);
    if(fork()==0)
    {
        close(p[1]);
        // char buf[10];
        int *temp = (int*)malloc(sizeof(int) * MAXSIZE);
        // int flag;
        for(int i = 0;i<count;i++){
            read(p[0],&temp[i],sizeof(int));
            // fprintf(2,"flag = %d ",flag);
            // fprintf(2,"%d ",temp[i]);
            // temp[i] = atoi(buf);
        }
        // for(int i = 0;i<count;i++){
        //     fprintf(2,"%d ",temp[i]);
        // }
        // close(p[1]);
        primeSieve(temp,count);
        exit(0);
    }


    // fprintf(1,"    %d %d\n",count,getpid());
    
    close(p[0]);
    free(a);
    wait((int*)0);
    exit(0);
}
int 
main()
{
    int *a = (int*)malloc(sizeof(int) * MAXSIZE);
    for (int i = 2 ; i <= MAXSIZE; i++)
    {
        a[i-2] = i;
    }
    primeSieve(a,34);
    exit(0);
}
