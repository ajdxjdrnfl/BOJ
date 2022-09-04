#include <stdio.h>
#include <string.h>
#define INF 100000001
typedef struct _NODE{
    int lar;
    int left;
    int right;
    int mid;
    int sum;
}NODE;

int max(int a, int b){
    return a>b?a:b;
}
void update(NODE *tree, int node, int start, int end, int left, int right, int value){
    if(left>end || right<start) return;
    if(start==end){
        tree[node].lar = value;
        tree[node].left = value;
        tree[node].right = value;
        tree[node].mid = value;
        tree[node].sum = value;
        return;
    }

    int mid =(start+end)/2;
    update(tree, node*2, start, mid, left, right, value);
    update(tree, node*2+1, mid+1, end, left, right, value);
    tree[node].mid = tree[node*2].right+tree[node*2+1].left;
    tree[node].sum = tree[node*2].sum+tree[node*2+1].sum;
    tree[node].left = max(tree[node*2].left, tree[node*2].sum + tree[node*2+1].left);
    tree[node].right = max(tree[node*2+1].right, tree[node*2+1].sum+tree[node*2].right);
    tree[node].lar = max(tree[node].left, max(tree[node].right, max(tree[node*2].lar , max(tree[node*2+1].lar, tree[node].mid))));
}
NODE query(NODE *tree, int node, int start, int end, int left, int right){
    NODE temp;


    if(left>end || right<start){
        temp.left = -INF;
        temp.right = -INF;
        temp.mid = -INF;
        temp.lar = -INF;
        temp.sum = 0;
        return temp;
    } 
    if(left<=start && end <=right) return tree[node];

    int mid = (start+end)/2;
    NODE left_node = query(tree, node*2, start, mid, left, right);
    NODE right_node = query(tree, node*2+1, mid+1, end, left, right);
    temp.sum = left_node.sum + right_node.sum;
    temp.left = max(left_node.left,  left_node.sum + right_node.left); 
    temp.right = max(right_node.right, right_node.sum + left_node.right);
    temp.mid = left_node.right + right_node.left;
    temp.lar = max(temp.left, max(temp.right, max(left_node.lar , max(right_node.lar, temp.mid))));
    return temp;
}
int main(void){

    int N;
    scanf("%d", &N);
    int n =1;
    while(N>=n) n*=2;
    n *= 2;
    NODE tree[n+1];
    memset(tree, 0 ,sizeof(tree));
    for(int i=1; i<=N; i++){
        int temp;
        scanf("%d", &temp);
        update(tree, 1, 1, N, i,i,temp);
    }
    int Q;
    scanf("%d", &Q);
    for(int i=1; i<=Q; i++){
        int l,r;
        scanf("%d %d", &l ,&r);
        NODE temp = query(tree, 1, 1, N, l, r);
        printf("%d\n", temp.lar);
    }
}