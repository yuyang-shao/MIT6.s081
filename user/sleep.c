#include "kernel/types.h"
#include "user/user.h"

int
main(int argc,char *argv[])
{
    if(argc <= 1){
        fprintf(2,"ERROR: sleep need an argument");
        exit(1);
    }else{
        int ticks = atoi(argv[1]);
        sleep(ticks);
    }
    exit(0);    
}