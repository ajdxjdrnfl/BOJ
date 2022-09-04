#include <stdio.h>

int dp[100][10001];
int max(int a, int b){
    if(a>b) return a;
    else return b;
}
int main(void){
    int N,M;
    int ans;
    scanf("%d %d", &N, &M);
    int byte[N], cost[N];
    for(int i=0; i<N; i++){
        scanf("%d", &byte[i]);
    }
    for(int i=0; i<N; i++){
        scanf("%d", &cost[i]);
    }
    for(int i=0; i<=10000; i++){
        if(cost[N-1]<=i) dp[N-1][i] = byte[N-1];
        else dp[N-1][i] = 0;
    }
    for(int i=N-2; i>=0; i--){
        for(int j=0; j<=10000; j++){
            if(j>=cost[i]) dp[i][j] = max(dp[i+1][j], dp[i+1][j-cost[i]]+byte[i]);
            else dp[i][j] = dp[i+1][j];
        }
    
    
    }
    for(int i=0; i<=10000; i++){
      
        if(dp[0][i]>=M){
            ans = i;
            break;
        }
    }
    printf("%d\n", ans);
    
}