#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<ctype.h>
#include<sys/wait.h>
#define BUFFER_SIZE 100
int is_palindrome(char *str){
    int len=strlen(str);
    for(int i=0;i<len/2;i++){
        if(str[i] != str[len-i-1])
            return 0;
    }
    return 1;
}
int main(){
    int fd[2];//fd[0]-read fd[1]-write
    pid_t pid;
    char str[BUFFER_SIZE];
    
    if(pipe(fd)==-1){
        perror("Pipe fail");
        return 1;
    }
    pid=fork();
    if(pid <0 ){
        perror("Fork failed");
        return 1;
    }
    if(pid>0){
        //Parent process
        close(fd[0]);
        printf("Enter a string to check palindrome \n");
        fgets(str,BUFFER_SIZE,stdin);
        str[strcspn(str,"\n")]='\0';
        write(fd[1],str,strlen(str)+1);
        close(fd[1]);
        wait(NULL);
        
    }
    else{
        close(fd[1]);
        char received_str[BUFFER_SIZE];
        read(fd[0],received_str,BUFFER_SIZE);
        close(fd[0]);
        if(is_palindrome(received_str)){
            printf("String is palindrome");
        }
        else{
            printf("String is not palindrome");
        }
    }
    return 0;
}