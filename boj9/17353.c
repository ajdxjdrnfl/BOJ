#include <stdio.h>
#include <string.h>

typedef long long ll;
ll min(ll a, ll b){
    return a<b?a:b;
}
ll max(ll a, ll b){
    return a>b?a:b;
}
void lazy_update(ll *tree, ll *lazy, int *count, int node, int start, int end){
    if(lazy[node]){
        tree[node] += ((end-start+1)*(2*lazy[node]+count[node]*(end-start))/2);
        if(start!=end){
            int mid = (end+start)/2;
            lazy[node*2] += lazy[node];
            count[node*2] += count[node];
            lazy[node*2+1] += (lazy[node]+count[node]*(mid+1-start));
            count[node*2+1] += count[node];
        }
        lazy[node] = 0;
        count[node] = 0;
    }
}

void init(ll *tree, int node, int start, int end, int left, int right, ll value){
    if(left>end || right<start) return;
    if(start==end ){
         tree[node]+= value;
         return;
    }
    int mid =(start+end)/2;
    init(tree, node*2, start, mid, left, right, value);
    init(tree, node*2+1, mid+1, end, left, right, value);
}

void update(ll *tree, ll *lazy, int *count, int node, ll start, ll end, int left, int right){
    lazy_update(tree, lazy, count, node, start, end);
    if(left>end || right<start) return;
    if(left<=start && end<=right){
        ll value = start-left+1;
        tree[node] += ((end-start+1) * (2*value+end-start)/2);
        if(start!=end){
            int mid = (start+end)/2;
            lazy[node*2] += value;
            count[node*2]++;
            lazy[node*2+1] += (value+mid+1-start);
            count[node*2+1]++;
        }
        return ;
    }

    int mid = (start+end)/2;
    update(tree, lazy, count, node*2, start, mid, left, right);
    update(tree, lazy, count, node*2+1, mid+1, end, left, right);
    tree[node] = tree[node*2] + tree[node*2+1];
    return ;
}

ll query(ll *tree, ll *lazy, int *count, int node, int start, int end, int left, int right){
    lazy_update(tree, lazy, count, node, start, end);
    if(left>end || right<start) return 0;
    if(left<=start && end <= right) return tree[node];

    int mid = (start+end)/2;
    return query(tree, lazy, count, node*2, start, mid, left, right) + query(tree, lazy, count, node*2+1, mid+1, end, left, right);
}

int main(void){
    int N, Q;
    scanf("%d", &N);
    int n=1;
    while(N>=n) n*=2;
    n*=2;
    ll tree[n+1];
    ll lazy[n+1];
    int count[n+1];
    memset(tree, 0 ,sizeof(tree));
    memset(lazy, 0, sizeof(lazy));
    memset(count, 0 ,sizeof(count));
    for(int i=1; i<=N; i++){
        ll temp;
        scanf("%lld", &temp);
        init(tree,  1, 1, N, i, i, temp);
    }
    scanf("%d", &Q);
    for(int i=1; i<=Q; i++){
        int temp;
        scanf("%d", &temp);
        if(temp==1){
            int a,b;
            scanf("%d %d", &a, &b);
            update(tree, lazy, count, 1, 1, N, a, b);
        }
        else if(temp==2){
            int a;
            scanf("%d", &a);
            printf("%lld\n", query(tree, lazy, count, 1, 1, N, a, a));

        }
    }
}