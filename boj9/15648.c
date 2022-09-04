#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bean[500001];
int dp[500001];
int max(int a, int b){
    return a>b?a:b;
}
int min(int a, int b){
    return a<b?a:b;
}
void update(int *tree, int node, int start, int end, int left, int right, int value){
    if(left>end || right<start) return;
    if(start==end){
        tree[node] = max(tree[node], value);
        return;
    }

    int mid = (start+end)/2;
    update(tree, node*2, start, mid, left, right, value);
    update(tree, node*2+1, mid+1, end, left, right, value);
    tree[node] = max(tree[node*2] , tree[node*2+1]);
    return;
}

int query(int *tree, int node, int start, int end, int left, int right){
    if(left>end || right<start) return 0;
    if( left <= start && end <= right) return tree[node];

    int mid = (start+end)/2;
    return max(query(tree, node*2, start, mid, left, right) , query(tree, node*2+1, mid+1, end, left, right));
}

int main(void){

    int N,k,d;
    scanf("%d %d %d", &N, &k, &d);
    for(int i=1; i<=N; i++){
        scanf("%d", &bean[i]);
    }
    
    memset(dp, 0 ,sizeof(dp));
    int mod_n=1;
    while(k>=mod_n) mod_n *= 2;
    mod_n*=4;
    int modTree[mod_n+1];
    memset(modTree, 0 ,sizeof(modTree));

    int query_n=1;
    while(500000>=query_n) query_n*=2;
    
    query_n *= 2;
    int querytree[query_n+1];
    memset(querytree, 0, sizeof(querytree));

    for(int i=N; i>=1; i--){
        dp[i]  = max(query(modTree, 1, 0, k-1, bean[i]%k, bean[i]%k), query(querytree, 1, 1, 500000, max(bean[i]-d, 1), min(500000, bean[i]+d)))+1;
        update(modTree, 1, 0, k-1, bean[i]%k, bean[i]%k, dp[i]);
        update(querytree, 1, 1, 500000, bean[i], bean[i], dp[i]);
    }
    int lar = -1;
    for(int i=1; i<=N; i++){
        lar = max(lar, dp[i]);
    }
    printf("%d\n", lar);
}