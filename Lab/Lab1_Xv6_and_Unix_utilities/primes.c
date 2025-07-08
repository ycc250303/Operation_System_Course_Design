#include "kernel/types.h" 
#include "user/user.h"

void get_primes(int p1[2]){
    close(p1[1]);
    int n; // 当前数字
    int tag = read(p1[0],&n,4);
    if(tag == 0){
        close(p1[0]);
        exit(0);
    }

    printf("prime %d\n",n);
    int p2[2];
    pipe(p2);
    int pid = fork();
    
    if(pid == 0){
        get_primes(p2);
    }
    else{
        int m;
        close(p2[0]);
        while(read(p1[0],&m,4)){
            if(m%n!=0){
                write(p2[1],&m,4);           
            }
        }
        close(p2[1]);
        wait(0);
    }
}

int
main(){
    int p[2];
    pipe(p);
    for(int i = 2;i<35;i++){
        write(p[1],&i,4);
    }
    get_primes(p);
    exit(0);
}