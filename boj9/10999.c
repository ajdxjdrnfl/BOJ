#include <stdio.h>
#include <string.h>

typedef long long ll;

void lazy_update(ll* tree, ll*lazy, int node, int start, int end){

    if(lazy[node]){
        tree[node] += (end-start+1)*lazy[node];

        if(start!=end){
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update(ll *tree, ll *lazy, int node, int start, int end, int left, int right, ll value){

    lazy_update(tree, lazy, node, start, end);
    if(left>end || right<start) return ;
    if(left<=start && end <= right){
        tree[node] += (end-start+1)*value;
        if(start!=end){
            lazy[node*2] += value;
            lazy[node*2+1] += value;
        }
        return;
    }

    int mid = (start+end)/2;
    update(tree, lazy, node*2, start, mid, left, right, value);
    update(tree, lazy, node*2+1, mid+1, end, left, right, value);
    tree[node] = tree[node*2] + tree[node*2+1];
    return ;
}

ll query(ll* tree, ll*lazy, int node, int start, int end, int left, int right){
    lazy_update(tree, lazy, node, start, end);
    if(left>end || right<start) return 0;
    if(left<=start && end<=right) return tree[node];
    int mid =(start+end)/2;
   
    return query(tree, lazy, node*2, start, mid, left, right)+query(tree,lazy,node*2+1, mid+1, end, left, right);
}

int main(void){

    int N,M,K;
    scanf("%d %d %d", &N, &M, &K);

    int n=1;
    while(N>=n) n*= 2;
    n*=4;

    ll tree[n+1];
    ll lazy[n+1];

    memset(tree, 0 ,sizeof(tree));
    memset(lazy, 0 , sizeof(lazy));

    for(int i=0; i<N; i++){
        ll num;
        scanf("%lld", &num);
        update(tree, lazy, 1, 1, N, i+1, i+1, num);
    }
   
    for(int i=0; i<M+K; i++){
        int a;
        scanf("%d", &a);
        if(a==1){
            ll b,c,d;
            scanf("%lld %lld %lld", &b, &c, &d);
            update(tree, lazy, 1, 1, N, b,c,d);
        }
        else if(a==2){
            ll b,c;
            scanf("%lld %lld", &b, &c);
            printf("%lld\n",query(tree, lazy, 1, 1, N, b, c));
        }
    }
}