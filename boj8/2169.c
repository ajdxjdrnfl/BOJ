#include <stdio.h>

#define MIN -100000001
int cost[1001][1001];
int left[1001][1001];
int right[1001][1001];
int dp[1001][1001];

int max(int a, int b){
    return a>b?a:b;
}
int robot(int i, int j, int N, int M);
int l(int i, int j, int N, int M){
    
    if(i==1 && j==1) return cost[i][j];
    if(j==M) return robot(i-1, j, N, M)+cost[i][j];
    if(j>M) return MIN;
    if(left[i][j]!=MIN) return left[i][j];

    left[i][j] = max(l(i, j+1, N, M), robot(i-1, j, N, M)) +cost[i][j];
    return left[i][j];
}
int r(int i, int j, int N, int M){
    if(i==1 && j==1) return cost[i][j];
    if(j==1) return robot(i-1, j, N, M) + cost[i][j];
    if(j<1) return MIN;
    if(right[i][j]!=MIN) return right[i][j];

    right[i][j] = max(r(i, j-1, N, M), robot(i-1, j ,N, M)) + cost[i][j];
    return right[i][j];
}

int robot(int i, int j, int N, int M){
    
    if(i<1) return MIN;
    if(dp[i][j]!=MIN) return dp[i][j];

    dp[i][j] = max(max(l(i, j+1, N,M ) , r(i, j-1, N, M)), robot(i-1, j, N, M))+cost[i][j];
    return dp[i][j];
}
int main(void){

    int N,M;
    scanf("%d %d", &N, &M);
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            scanf("%d", &cost[i][j]);
            dp[i][j] = MIN;
            right[i][j] = MIN;
            left[i][j] = MIN;
        }
    }
    dp[1][1] = cost[1][1];
    robot(N,M , N, M);
    printf("%d\n", dp[N][M]);
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }
}