#include <stdio.h>
#include <string.h>

typedef long long ll;

ll T[100001];
ll V[100001];
ll dp[100001];

int max(int a, int b){
    return a>b?a:b;
}

int min(int a, int b){
    return a<b?a:b;
}
void dnc(int N, int D, int left, int right, int low, int high){
    
    if(left>right) return;
    
    int mid = (left+right)/2;
    int index = max(low, mid);
    int lo = max(low, mid);
    int hi = min(mid+D, high);
    for(int i=lo; i<=hi; i++){
        if(dp[mid] < (i-mid)*T[i] + V[mid]){
            dp[mid] = (i-mid)*T[i] + V[mid];
            index = i;
        }        
    }
    dnc(N, D, left, mid-1, low, index);
    dnc(N, D, mid+1, right, index, high);
}

int main(void){

    int N,D;
    scanf("%d %d", &N, &D);
    for(int i=0; i<N; i++){
        scanf("%lld", &T[i]);
    }
    for(int i=0; i<N; i++){
        scanf("%lld", &V[i]);
    }

    memset(dp, 0 , sizeof(dp));
    dnc(N,D, 0, N-1, 0, N-1);

    ll ans=0;
    for(int i=0; i<N; i++){
        if(ans<dp[i]) ans=dp[i];
    }
    printf("%lld\n", ans);

    
}