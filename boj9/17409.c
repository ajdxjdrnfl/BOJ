#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
int arr[100001];

void update(int *tree, int node, int start, int end,int left, int right, int value){
    
    if(left>end || right < start) return;
    if(start==end){
        tree[node] = (tree[node]+value)%MOD;
        return;
    }
    int mid = (start+end)/2;
    update(tree, node*2, start, mid, left, right, value);
    update(tree, node*2+1, mid+1, end, left, right, value);
    tree[node] = (tree[node*2]+tree[node*2+1])%MOD;
}

int query(int *tree, int node, int start, int end, int left, int right){
    if(left>end || right<start) return 0;
    if(left<=start && end<=right) return tree[node];
    int mid = (start+end)/2;
    return (query(tree, node*2, start, mid, left, right) + query(tree, node*2+1, mid+1, end, left, right))%MOD;
}
int main(void){
    int N,K;
    scanf("%d %d", &N, &K);
    for(int i=1; i<=N; i++){
        scanf("%d", &arr[i]);
    }
    int n =1;
    while(N>=n) n*=2;
    n*=4;
    int tree[K+1][n+1];
    memset(tree, 0 , sizeof(tree));

    for(int i=N; i>=1; i--){
        update(tree[1], 1, 1, N , arr[i], arr[i], 1);
        for(int j=2; j<=K; j++){
            update(tree[j], 1, 1, N, arr[i], arr[i], query(tree[j-1], 1, 1, N, arr[i]+1, N));
        }
    }
    printf("%d\n", tree[K][1]);
}