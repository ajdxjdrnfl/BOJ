#include <stdio.h>

#define INF 500001

typedef long long ll;
typedef struct _NODE{
    ll above;
    ll below;
}NODE;

ll min(ll a, ll b){
    return a<b?a:b;
}

ll max(ll a, ll b){
    return a>b?a:b;
}

void add(NODE *from, NODE *to){
   to->above = min(max(from->above, to->above), from->below);
    to->below = min(max(from->above, to->below), from->below);
}
void update(NODE *tree, int node, int start, int end, int left, int right, int above, int below){

    if(start!=end){
        add(&tree[node], &tree[node*2]);
        add(&tree[node], &tree[node*2+1]);
        tree[node].above = 0;
        tree[node].below = INF;
    }
    
    if(left>end || right<start) return;
    if(left<=start && end<=right){
        NODE temp;
        temp.below = below;
        temp.above = above;
        add(&temp, &tree[node]);
        return;
    }

    int mid = (start+end)/2;
    update(tree, node*2, start, mid, left, right, above, below);
    update(tree, node*2+1, mid+1, end, left, right, above, below);
    return;
}

NODE query(NODE* tree, int node, int start, int end, int index){


    if(start!=end){
        add(&tree[node], &tree[node*2]);
        add(&tree[node], &tree[node*2+1]);
        tree[node].above =0;
        tree[node].below = INF;
    }
    if(start==end && start == index) return tree[node];
    int mid =(start+end)/2;
    if(mid>=index) return query(tree, node*2, start, mid, index);
    else return query(tree, node*2+1, mid+1, end, index);
}
int main(void){

    int N,k;
    scanf("%d %d", &N, &k);

    int n=1;
    while(N>=n) n*=2;
    n*=4;
    NODE tree[n+1];
    for(int i=1; i<=n; i++){
        tree[i].above = 0;
        tree[i].below = INF;
    }

    for(int i=0; i<k; i++){
        int op,l,r;
        ll h;
        scanf("%d %d %d %lld", &op, &l, &r, &h);
        if(op==1) update(tree, 1, 1, N, l+1, r+1, h, INF );
        else if(op==2) update(tree, 1, 1, N, l+1, r+1, 0,  h);
        
    }
    for(int j=1; j<=N; j++){
        NODE temp = query(tree, 1, 1, N, j);
        printf("%lld\n", temp.above);
    }

}