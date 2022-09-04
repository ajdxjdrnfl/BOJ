#include <stdio.h>

int max(int a, int b){
    if(a>b) return a;
    else return b;
}
int main(void){
    int N,K;
    
    scanf("%d %d", &N, &K);
    int w[N+1], v[N+1];
    int dp[N+1][K+1];
    for(int i=1; i<=N; i++){
        scanf("%d %d", &w[i], &v[i]);
    }
    
    for(int i=0; i<=N;  i++){
        for(int j=0; j<=K;  j++){
            dp[i][j] = 0;
        }
    }
    for(int i=1; i<=N; i++){

        for(int j=1; j<=K; j++){
            if(j-w[i] >=0) dp[i][j] = max(dp[i-1][j-w[i]] +v[i], dp[i-1][j]);  
            else dp[i][j] = dp[i-1][j];
        }
    }

    printf("%d\n", dp[N][K]);
}