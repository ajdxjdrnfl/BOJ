#include <stdio.h>

int main(void){

    int N,largest;
    scanf("%d", &N);
    int arr[N];
    int dp[N];
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }
    dp[0]=arr[0];
    for(int i=1; i<N; i++){
        if(dp[i-1] + arr[i] < arr[i]) dp[i] = arr[i];
        else dp[i] = dp[i-1] + arr[i];
    }

    for(int i=0; i<N; i++){
        if(i==0) largest = dp[i];
        if(largest < dp[i]) largest = dp[i];
    }

    printf("%d\n", largest)
    
}