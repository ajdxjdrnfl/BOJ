#include <stdio.h>
#include <string.h>

#define INF 0x3f3f3f3f3f3f3f3f;
typedef long long ll;

ll sum[8001];
ll dp[801][8001];

int min(int a, int b){
    return a<b?a:b;
}
int max(int a, int b){
    return a>b?a:b;
}

void jail(int G, int left, int right, int low, int high){
    
    if(left>right) return;
    int mid = (left+right)/2;
    int hi = min(high, mid-1);   
    int index = low;
    for(int i=low; i<=hi; i++){
        if(dp[G][mid] > dp[G-1][i] + (mid-i)*(sum[mid]-sum[i])){
            dp[G][mid] = dp[G-1][i] + (mid-i)*(sum[mid]-sum[i]);
            index = i;
        }
    }
    
    jail(G, left, mid-1, low, index);
    jail(G, mid+1, right, index, high);
}
int main(void){

    int L,G;
    scanf("%d %d", &L, &G);
    if(G>=L) G=L;
    memset(sum, 0 , sizeof(sum));
    memset(dp, 0 , sizeof(dp));
    for(int i=0; i<L; i++){
        ll temp;
        scanf("%lld", &temp);
        if(i!=0) sum[i] += (sum[i-1] + temp);
        else sum[i] = temp;
    }    
    for(int i=0; i<=G; i++){
        for(int j=0; j<L; j++){
            dp[i][j] = INF;
        }
    }
    for(int i=0; i<L; i++){
        dp[1][i] = (i+1)*sum[i];
    }
    for(int i=2; i<=G; i++){
        jail(i, 0, L-1, 0, L-1);
    }


    printf("%lld\n", dp[G][L-1]);
}