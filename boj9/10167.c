#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF 3000000000001
typedef long long ll;
typedef struct _POINT{
    ll x;
    ll y;
    ll w;
    int num;
}POINT;

typedef struct _NODE{
    ll left;
    ll right; 
    ll sum;
    ll mid;
    ll max;
}NODE;

int comx(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;

    if(pa.x<pb.x) return -1;
    else if(pa.x>pb.x) return 1;
    else return 0;
}
int comp(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    
    if(pa.y<pb.y) return -1;
    else if(pa.y>pb.y) return 1;
    else return 0;
}

ll max(ll a, ll b){
    return a>b?a:b;
}
void update(NODE *tree, int node, int start, int end, int left, int right, ll value){

    if(left>end || right<start) return;
    if(start==end){
        tree[node].left += value;
        tree[node].right += value;
        tree[node].mid += value;
        tree[node].sum += value;
        tree[node].max += value;
        return ;
    }

    int mid = (start+end)/2;
    update(tree, node*2, start, mid, left, right, value);
    update(tree, node*2+1, mid+1, end, left, right, value);
    
    tree[node].left = max(tree[node*2].sum + tree[node*2+1].left,  tree[node*2].left);
    tree[node].right = max(tree[node*2+1].sum + tree[node*2].right, tree[node*2+1].right);
    tree[node].mid = tree[node*2].right + tree[node*2+1].left;
    tree[node].sum = tree[node*2].sum + tree[node*2+1].sum;
    tree[node].max = max(tree[node].left, max(tree[node].right, max(tree[node].mid, max(tree[node*2].max, tree[node*2+1].max))));


}

NODE query(NODE *tree, int node, int start, int end, int left, int right){

    NODE temp;
    if(left>end || right<start){
        temp.left = -INF;
        temp.right = -INF;
        temp.mid = -INF;
        temp.sum = 0;
        temp.max = -INF;
        return temp;
    }
    if(left <= start && end<= right) return tree[node];

    int mid = (start+end)/2;
    NODE left_node = query(tree, node*2, start, mid, left, right);
    NODE right_node = query(tree, node*2+1, mid+1, end, left, right);
    
    temp.left = max(left_node.left, left_node.sum + right_node.left);
    temp.right = max(right_node.right, right_node.sum + left_node.right);
    temp.mid = left_node.right + right_node.left;
    temp.sum = left_node.sum + right_node.sum;
    temp.max = max(temp.left, max(temp.right, max(temp.mid, max(left_node.max, right_node.max))));

    return temp;
}

int main(void){
    int N;
    scanf("%d", &N);
    POINT p[3001];
    for(int i=0; i<N; i++){
        scanf("%lld %lld %lld", &p[i].x, &p[i].y, &p[i].w);
    }
    int n=1;
    while(N>=n) n*= 2;
    n*=4;


    qsort(p, N, sizeof(POINT), comp);

    int c_size=0;
    ll last = p[0].y;
    p[0].y = ++c_size;

    for(int i=1; i<N; i++){
        if(p[i].y != last){
            last = p[i].y;
            p[i].y = ++c_size;
        }
        else p[i].y = c_size;
    }

    qsort(p, N, sizeof(POINT), comx);
    ll ans = -INF;   
    for(int i=0; i<N; i++){
        if(i>=1 && p[i].x == p[i-1].x) continue;
        NODE tree[n+1];
        memset(tree, 0 , sizeof(tree));
        for(int j=i; j<N; j++){
            update(tree, 1, 1, c_size, p[j].y, p[j].y, p[j].w);
            if(j==N-1 || p[j].x!=p[j+1].x){
            NODE temp = query(tree, 1, 1, c_size, 1, c_size);
            ans = max(ans, temp.max);
            }
        }
        
        
    }
    printf("%lld\n", ans);
}