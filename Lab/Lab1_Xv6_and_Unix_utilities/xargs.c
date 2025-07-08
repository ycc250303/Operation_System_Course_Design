#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

#define BUFFER_SIZE 512

int
main(int argc,char *argv[]){
    sleep(10);

    // 获取前一个命令的标准化输出
    char buf[BUFFER_SIZE];
    read(0,buf,BUFFER_SIZE);

    // 获取自己的命令行参数
    char *xargv[MAXARG];
    int xargc = 0;

    for(int i=1;i<argc;i++){
        xargv[xargc] = argv[i];
        xargc++;
    }

    char *p = buf;
    for(int i = 0;i < BUFFER_SIZE;i++){
        if(buf[i] == '\n'){
            int pid = fork();
            if(pid > 0){
                p = &buf[i+1];
                wait(0);
            }
            else{
            // 使用 exec去执行命令
                buf[i] = 0;
                xargv[xargc] = p;
                xargc++;
                xargv[xargc] = 0; // 对于exec，xargv最后一个元素必须是0
                xargc++;

                exec(xargv[0],xargv);
                exit(0);
            }
        }
    }

    exit(0);
}