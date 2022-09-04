#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MOD 1000000007

typedef long long ll;

void lazy_update(ll *tree, ll **lazy, int node, int start, int end){

    if(lazy[node][0]==1 && lazy[node][1] ==0) return;
    
    tree[node] = (lazy[node][0]*tree[node] + (end-start+1)*lazy[node][1])%MOD;
    if(start!=end){
        
        lazy[node*2][0] = (lazy[node*2][0]*lazy[node][0])%MOD;
        lazy[node*2+1][0] = (lazy[node*2+1][0]*lazy[node][0])%MOD;

        lazy[node*2][1] = (lazy[node*2][1]*lazy[node][0] + lazy[node][1])%MOD;
        lazy[node*2+1][1] = (lazy[node*2+1][1]*lazy[node][0] + lazy[node][1])%MOD;
    }
    lazy[node][0] = 1;
    lazy[node][1] = 0;
}
void update(ll *tree, ll **lazy, int node, int start, int end, int left , int right, ll mul, ll value){
    lazy_update(tree, lazy, node, start, end);

    if(left>end || right < start) return;
    if(left<=start && end<=right){
        tree[node] = (tree[node]*mul + (end-start+1)*value)%MOD;
        if(start!=end){
            lazy[node*2][0] = (lazy[node*2][0]*mul)%MOD;
            lazy[node*2+1][0] = (lazy[node*2+1][0]*mul)%MOD;

            lazy[node*2][1] = (lazy[node*2][1]*mul + value)%MOD;
            lazy[node*2+1][1] = (lazy[node*2+1][1]*mul + value)%MOD; 
        }
        return;
    }
    
    int mid = (start+end)/2;
    update(tree, lazy, node*2, start, mid, left, right, mul, value);
    update(tree, lazy, node*2+1, mid+1, end, left, right, mul, value);
    tree[node] = (tree[node*2]+tree[node*2+1])%MOD;
    return ;
}

ll query(ll *tree, ll**lazy, int node, int start, int end, int left, int right){
    lazy_update(tree, lazy, node, start, end);
    if(left>end || right<start) return 0;
    if(left<=start && end<=right) return tree[node];
    int mid =(start+end)/2;
    return (query(tree, lazy, node*2, start, mid, left, right) + query(tree, lazy, node*2+1, mid+1, end, left, right))%MOD;
}
int main(void){

    int N,M;
    scanf("%d", &N);
    int n=1;
    while(N>=n) n*= 2;
    n*=4;

    ll tree[n+1];
    ll **lazy = (ll**)malloc(sizeof(ll*)*(n+1));

    memset(tree, 0 ,sizeof(tree));
    for(int i=1; i<=n; i++){
        lazy[i] = (ll*)malloc(sizeof(ll)*2);
        lazy[i][0] = 1;
        lazy[i][1] = 0;
    }
    
    for(int i=0; i<N; i++){
        ll temp;
        scanf("%lld", &temp);
        update(tree, lazy, 1, 1, N, i+1, i+1, 1, temp);
    }
    scanf("%d", &M);
    for(int i=0; i<M; i++){
        int a,b,c;
        scanf("%d %d %d", &a, &b, &c);
        if(a==1){
            ll d;
            scanf("%lld", &d);
            update(tree, lazy, 1, 1, N, b, c, 1, d);
        }
        if(a==2){
            ll d;
            scanf("%lld", &d);
            update(tree, lazy, 1, 1, N, b, c, d, 0);
        }
        if(a==3){
            ll d;
            scanf("%lld", &d);
            update(tree, lazy, 1, 1, N, b, c, 0, d);
        }
        if(a==4){
            printf("%lld\n", query(tree, lazy, 1, 1, N, b, c));
        }
    }

}