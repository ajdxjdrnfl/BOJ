#include <stdio.h>
#include <string.h>

void lazy_update(int *tree, int *lazy, int node, int start, int end){

    if(lazy[node]%2==1){
        tree[node] = (end-start+1) - tree[node];
        if(start!=end){
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }

        lazy[node] = 0;
    }
}
void update(int *tree, int *lazy, int node, int start, int end, int left, int right){
    lazy_update(tree, lazy, node, start, end);

    if(left>end || right<start) return;
    if(left<=start && end <=right){
        tree[node] = (end-start+1) - tree[node];
        if(start!=end){
            lazy[node*2]  += 1;
            lazy[node*2+1] += 1;
        }
        return ;
    }
    int mid = (start+end)/2;
    update(tree, lazy, node*2, start, mid, left, right);
    update(tree, lazy, node*2+1, mid+1, end, left, right);
    tree[node] = tree[node*2] + tree[node*2+1];
    return;
}

int query(int *tree, int *lazy, int node, int start, int end, int left, int right){

    lazy_update(tree, lazy, node, start ,end);
    if(left>end || right<start) return 0;
    if(left<=start && end<=right) return tree[node];
    int mid= (start+end)/2;
    return query(tree, lazy, node*2, start , mid, left, right)+query(tree, lazy, node*2+1, mid+1, end, left, right);

}
int main(void){

    int N, M;
    scanf("%d %d", &N, &M);

    int n=1;
    while(N>=n) n*=2;
    n *= 4;

    int tree[n+1];
    int lazy[n+1];
    memset(tree, 0 ,sizeof(tree));
    memset(lazy,0,sizeof(lazy));
   
    
    for(int i=0; i<M; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if(a==0){
            update(tree, lazy, 1, 1, N, b, c);
        }
        else if(a==1){
            printf("%d\n",query(tree, lazy, 1, 1, N, b, c));
            
        }
    }

}