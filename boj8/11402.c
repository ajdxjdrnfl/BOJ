#include <stdio.h>
#include <string.h>
long long dp[2001][2001];
long long binomial(int a, int b, long long p){
    if(dp[a][b]!=-1) return dp[a][b];

    if(b==0 || a==b) return 1;
    long long ans =1;
    ans = (binomial(a-1,b-1,p)+binomial(a-1, b,p))%p;
    dp[a][b] = ans;
    return dp[a][b];
}

long long lucas(long long N, long long K, long long M){
    
    int vec1[100];
    int top_1=0;
    int vec2[100];
    int top_2=0;
    long long result =1;
    while(N){
        vec1[top_1++] = N%M;
        N = N / M ;
    }
    while(K){
        vec2[top_2++] = K%M;
        K = K / M;
    }
    
    for(int i=0; i<top_1; i++){
        int a,b;
        a = vec1[i];
        if(i<top_2) b = vec2[i];
        else b = 0;

        if(a<b) return 0;
        else result = (result*binomial(a,b, M))%M;       
    }
    return result;
}
int main(void){

    long long N,K,M;
    scanf("%lld %lld %lld", &N, &K, &M);
    memset(dp, -1, sizeof(dp));
    printf("%lld\n", lucas(N,K,M));
}