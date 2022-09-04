#include <stdio.h>

int dp[1000001]={0};
int tile( int N){
    if(dp[N]!=0 && N!=0) return dp[N];
    else if(N==0) return 0;
    else if(N==1) return 1;
    else if(N==2) return 2;

    else{
       dp[N] = (tile(N-2)+tile(N-1))%15746;
        
        return dp[N];
    }

}
int main(void){
    int N;
    scanf("%d" , &N);
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;

    tile(N);

    printf("%d", dp[N]%15746);
}