#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h" 

int main(int argc, char *argv[]) {
	int p[2];
    pipe(p); //creat a pipe

    int pid=fork();
    if(pid<0) fprintf(2,"fork erroe");

    if(pid>0){ //parent process
        write(p[1],"a",1);      //Write a byte to the pipeline
        close(p[1]);
        char c1;
        wait(0);            //Wait for the child process to exit before reading
        read(p[0],&c1,1);
        close(p[0]);
        printf("%d: received pong\n", getpid());
        
        
    }else{
        char c2;
        read(p[0],&c2,1);
        close(p[0]);
        printf("%d: received ping\n", getpid());

        write(p[1],"a",1);
        close(p[1]);
        exit(0);
    }
    exit(0);
}
