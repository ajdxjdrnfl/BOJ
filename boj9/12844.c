#include <stdio.h>
#include <string.h>

void lazy_update(int *tree, int *lazy, int node, int start, int end){
    
    if(lazy[node]){
        int index = end-start+1;
        if(index%2) tree[node] ^= lazy[node];
        if(start!=end){
            lazy[node*2] ^= lazy[node];
            lazy[node*2+1] ^= lazy[node];
        }
        lazy[node] = 0;
    }
}
void update(int *tree, int *lazy, int node, int start, int end, int left, int right, int value){
    lazy_update(tree, lazy, node, start, end);
    if(left>end || right<start) return ;
    if(left<=start && end <= right){
        int index = end-start+1;
        if(index%2) tree[node] ^= value;
        if(start!=end){
            lazy[node*2] ^= value;
            lazy[node*2+1] ^= value;
        }
        return ;
    }

    int mid =(start+end)/2;
    update(tree, lazy, node*2, start, mid , left, right, value);
    update(tree, lazy, node*2+1, mid+1, end, left, right, value);
    tree[node] = tree[node*2]^tree[node*2+1];
    return;
}

int query(int *tree, int*lazy, int node, int start, int end, int left, int right){

    lazy_update(tree, lazy, node, start, end);
    if(left>end || right<start) return 0;
    if(left<=start && end <= right) return tree[node];

    int mid = (start+end)/2;
    return query(tree, lazy, node*2, start, mid, left, right)^query(tree, lazy, node*2+1, mid+1, end, left, right);
}
int main(void){
    int N;
    scanf("%d", &N);
    int n=1;
    while(N>=n) n*=2;
    n*=4;
    int tree[n+1];
    int lazy[n+1];
    memset(tree, 0 ,sizeof(tree));
    memset(lazy, 0 , sizeof(lazy));
    for(int i=0; i<N; i++){
        int temp;
        scanf("%d", &temp);
        update(tree, lazy, 1, 1, N, i+1, i+1, temp);       
    }
    int M;
    scanf("%d", &M);
    for(int i=0; i<M; i++){
        int num;
        scanf("%d", &num);
        if(num==1){
            int a,b,c;
            scanf("%d %d %d", &a, &b, &c);
            update(tree, lazy, 1, 1, N, a+1, b+1, c);
        }
        else if(num==2){
            int a, b;
            scanf("%d %d", &a, &b);
            printf("%d\n", query(tree, lazy, 1, 1, N, a+1, b+1));
        }
    }
}