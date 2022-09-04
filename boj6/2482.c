#include <stdio.h>
#include <string.h>

long long dp[1001][1001];

#define mod 1000000003 
long long muncell(int N, int K){
    if(K==1) {
        return N;
    }
    if(K<=0) return 0;
    if(N <= K) return 0;
    if(dp[N][K]!= -1 ) return dp[N][K];
    dp[N][K] = (muncell(N-1, K) + muncell(N-2, K-1))%mod;
    return dp[N][K];

    
}
int main(void){

    int N,K;
    scanf("%d",&N);
    scanf("%d",&K);
    
    dp[0][0] = 1;
    memset(dp, -1, sizeof(dp));
    long long result = muncell(N, K);
    if(K==1) printf("%d", N);
    else if(K==2) printf("%lld", (result-1)%mod); 
    else printf("%lld", (result-muncell(N-4, K-2)+mod)%mod);
}