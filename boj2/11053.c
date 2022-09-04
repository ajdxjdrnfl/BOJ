#include <stdio.h>


int main(void){
    int N, largest;
    int arr[1001];
    int dp[1001];
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        scanf("%d", &arr[i]);
    }
    dp[N] = 1;
    for(int i=N-1; i>=1; i--){
        dp[i]=1;
        for(int j=i+1; j<=N; j++){
            if(arr[i]<arr[j]){
                if(dp[i] < dp[j]+1) dp[i] = dp[j] +1 ;
            }
        }
    }
    for(int i=1; i<=N; i++){
        if(i==1) largest = dp[1];
        else if(largest < dp[i]) largest = dp[i]; 
    }
    printf("%d\n", largest);
    
}