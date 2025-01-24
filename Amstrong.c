#include<stdio.h>
#include<math.h>
int is_amstrong(int num){
    int sum=0;
    int org=num;
    int c=0;
    while(org>0){
        org=org/10;
        c++;
    }
    org=num;
    while(org>0){
        int rem=org%10;
        sum=sum+pow(rem,c);
        org=org/10;
    }
    return(sum==num);
}
int main(){
    int num;
    printf("Enter a number\n");
    scanf("%d",&num);
    if(is_amstrong(num)){
        printf("Amstrong\n");
    }
    else{
        printf("Not Amstrong\n");
    }
    return 0;
}