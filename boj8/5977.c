#include <stdio.h>

long long E[100001];
long long dp[100001];
int deque[100002];

long long sum[100001];
int rear=0, front =0;

long long DP(int index){
    return dp[index-1] - sum[index];
}
int main(void){

    int N,K;
    scanf("%d %d", &N, &K);
    for(int i=0; i<N; i++){
        scanf("%lld", &E[i]);
        if(i!=0) sum[i] = sum[i-1]+E[i];
        else sum[i] = E[i];
    }
    deque[front++] = 0; 
    dp[0] = E[0];
    for(int i=1; i<N; i++){
        if(rear<front && deque[rear] < i-K) rear++;
        while(rear<front && DP(deque[front-1]) <= DP(i)) front--;
        deque[front++] = i;
        if(i+1<=K) dp[i] = sum[i];
        else dp[i] =  sum[i] + DP(deque[rear]);
        
    }
    
   printf("%lld\n", dp[N-1]);

}