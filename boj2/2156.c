#include <stdio.h>


int dp[10001];
int max(int a, int b){
    return a>b ? a:b;
}

int main(void){
    int N;
    int arr[10001];
    scanf("%d", &N);
    
    for(int i=1; i<=N; i++){
        scanf("%d", &arr[i]);
    }
    dp[0] = 0;
    dp[1] = arr[1];
    dp[2] = arr[2]+arr[1];
    
    for(int i=3; i<=N; i++){
        dp[i] = max(dp[i-1], max(dp[i-2]+arr[i], dp[i-3]+arr[i-1]+arr[i]));
    }
    
    printf("%d\n", dp[N]);
    


}