#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(){

    int number;
    pid_t pid;
    int fd[2];//fd[0]write fd[1]read
    if(pipe(fd)==-1){
        perror("Pipe failed\n");
        return 1;
    }
    pid=fork();
    if(pid<0){
        perror("Fork failed\n");
        return 1;
    }
    if(pid>0){
        close(fd[0]);
        printf("Enter a number\n");
        scanf("%d",&number);
        write(fd[1],&number,sizeof(number));
        close(fd[1]);
        wait(NULL);
    }
    else{
        close(fd[1]);
        read(fd[0],&number,sizeof(number));
        close(fd[0]);
        if(number%2==0){
            printf("Even\n");
        }
        else{
            printf("Odd\n");
        }
            exit(0);
    }



    return 0;
}