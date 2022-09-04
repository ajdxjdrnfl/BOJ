#include <stdio.h>
#include <string.h>

typedef long long ll;

#define INF 2500000000000
ll dp[5001][5001];
ll sum[5001];
int A[5001][5001];

ll C(int i, int j){
    return (sum[j]-sum[i-1]);
}
int min(int a, int b){
    return a<b?a:b;
}
int main(void){
    int T;
    scanf("%d", &T);
    while(T--){
        int K;
        
        scanf("%d", &K);
        memset(sum, 0, sizeof(sum));

        for(int i=1; i<=K; i++){
            ll temp;
            scanf("%lld", &temp);
            sum[i] = sum[i-1] + temp;
        }

        memset(dp,  0, sizeof(dp));        
        memset(A, 0 , sizeof(A));

        for(int i=1; i<=K; i++){
            for(int j=1; j<=K; j++){
                dp[i][j] = INF;
            }
        }
        for(int i=1; i<=K; i++){
            A[i][i] = i;
            dp[i][i] = 0;
        }
        
        for(int l=1; l<K; l++){
            for(int i=1; i<=K-l; i++){
                int j = i+l;
                for(int k = A[i][j-1] ; k<=min(A[i+1][j], j); k++){
                    ll temp = dp[i][k] + dp[k+1][j] + C(i,j);
                    if(temp < dp[i][j]){
                        dp[i][j] = temp;
                        A[i][j] = k;
                    }
                }
            }
        }
        printf("%lld\n", dp[1][K]);

    }
}