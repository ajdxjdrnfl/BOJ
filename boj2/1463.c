#include <stdio.h>
#include <stdlib.h>
int result = 0;
int *dp;

int makeOne(int num){
    int smallest;
    int index=0;
    if(dp[num]!=0) return dp[num];
    if(num==1) return 0;
    if(num%3==0){

        smallest = makeOne(num/3) + 1;
        index++;
    }
    if(num%2==0){
        int temp = makeOne(num/2) +1;
        if(index==0) smallest = temp;
        else if(smallest > temp) smallest = temp;
        index++;
    } 
    if(num>0){
        int temp = makeOne(num-1)+1;
        if(index ==0) smallest = temp;
        else if(smallest > temp) smallest = temp;
        index++;
    }

    dp[num] = smallest; 
    return dp[num];
}

int main(void){

    int num;
    
    scanf("%d", &num);
    dp = (int *)malloc(sizeof(int)*(num+1));
    dp[1] = 0;
    makeOne(num);
    printf("%d\n", dp[num]);
}