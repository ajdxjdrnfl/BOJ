#include <stdio.h>
#include <stdlib.h>

long long dp[101]={0,};

long long pado(int N){

    if(dp[N]!=0) return dp[N];
    else if(N==0) return 0;
    else{    
        dp[N] = pado(N-1) + pado(N-5);
    return dp[N];
    }
}

int main(void){
    int N;
    int *arr;
    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }
    dp[0]=0;
    dp[1]=1;
    dp[2]=1;
    dp[3]=1;
    dp[4]=2;


    for(int i=0; i<N; i++){
        printf("%lld\n", pado(arr[i]));
    }
    
}