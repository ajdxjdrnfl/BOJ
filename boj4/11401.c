#include <stdio.h>

#define MOD 1000000007;
#define TEMP 1;

int main(void){
    int N,K;
    long long result1 =1;
    long long result2 =1;
    scanf("%d %d", &N, &K);
    for(int i=K+1; i<=N; i++){
        result1 = (result1 * i) % MOD;
    }
    
    for(int i=1; i<=N-K; i++){
        result2 = (result2*i) %MOD;
    }
    int temp = TEMP+1;
    long long index = 1000000005;
    printf("%d\n", temp);
    while(index>0){
        if(index%2==1){
            result1 = (result1 * result2)%MOD;
        }
        index = index/2;
        result2 =  (result2*result2) %MOD;
    }
    printf("%lld\n", result1);

}