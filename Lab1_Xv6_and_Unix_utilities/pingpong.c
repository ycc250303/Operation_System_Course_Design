#include "kernel/types.h"
#include "user/user.h"

int
main(){
    int p[2];
    pipe(p);
    
    int pid = fork();
    if(pid == 0){ // 子进程
        close(p[1]); // 关闭写端
        read(p[0],&pid,4);
        printf("%d: received ping\n",getpid());
        close(p[0]); // 关闭读端
        exit(0); // 释放子进程资源
    }
    else{
        close(p[0]);
        write(p[1],&pid,4);
        close(p[1]);
        wait(0); // 等待子进程结束后再输出
        printf("%d: received pong\n",getpid());
    }

    exit(0);
}