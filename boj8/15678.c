#include <stdio.h>
#include <string.h>

long long bridge[100001];
long long dp[100001];

long long deque[100001];
int rear=0, front = 0;

long long max(long long a, long long b){
    return a>b?a:b;
}
int main(void){

    int N,D;
    scanf("%d %d", &N, &D);
    memset(dp, 0, sizeof(dp));
    for(int i=1; i<=N; i++){
        scanf("%lld", &bridge[i]);
    }
    
    for(int i=1; i<=N; i++){

        if(rear<front && deque[rear] < i-D) rear++;
        dp[i] = bridge[i];
        if(rear<front) dp[i] = max(dp[i] , dp[deque[rear]] + bridge[i]);
        while(rear<front && dp[deque[front-1]] <= dp[i]) front--;
        deque[front++] = i;
        
    }
    long long ans = dp[1];
    for(int i=1; i<=N; i++){
        ans = max(ans, dp[i]);
    }
    printf("%lld\n", ans);
    
    
}