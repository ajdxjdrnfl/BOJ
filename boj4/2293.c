#include <stdio.h>
int dp[10001];


int main(void){

    int n,k;
    scanf("%d %d", &n, &k);
    int value[n];
    for(int i=0; i<n; i++){
        scanf("%d", &value[i]);
    }
    dp[0]=1;
    for(int i=0; i<n; i++){
        for(int j=value[i]; j<=k ;j++){
            dp[j] += dp[j-value[i]];
        }
    }
    printf("%d\n", dp[k]);
}