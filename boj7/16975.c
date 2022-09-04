#include <stdio.h>
#include <string.h>
int arr[100001];
int tree[400001];
int lazy[400001];
int update(int node, int rear, int front, int start, int end, int value){

    if(front<start || rear > end) return tree[node] + lazy[node]*(end-start+1);

    if(rear<=start && end <=front){
        lazy[node] += value;
        return tree[node]+lazy[node]*(end-start+1);
    }

    if(lazy[node]!=0){
        tree[node] = tree[node] + (end-start+1) * lazy[node];
        if(start!=end){
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }

    int mid = (start+end)/2;
    int left= update(node*2, rear, front, start, mid, value);
    int right = update(node*2+1, rear, front, mid+1, end, value);
    tree[node] = left+right;
}

int init(int node, int start, int end){
    if(start==end){
        tree[node] = arr[start];
        return tree[node];
    }

    int mid = (start+end)/2;
    tree[node] = init(node*2, start, mid) + init(node*2+1, mid+1, end);
    return tree[node];
}
int query(int node, int index, int start, int end){
    if(index<start || index>end) return 0;
    if(start==end) return tree[node]+lazy[node];
    if(lazy[node]!=0){
        tree[node] = tree[node] + (end-start+1)*lazy[node];
        lazy[node*2] += lazy[node];
        lazy[node*2+1] += lazy[node];
        lazy[node] = 0;
    }
    int mid = (start+end)/2;
    if(mid>=index) return query(node*2, index, start, mid);
    else return query(node*2+1, index, mid+1, end);
}
int main(void){
    int N, M;
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        scanf("%d", &arr[i]);
    }
    memset(tree, 0 ,sizeof(tree));
    memset(lazy, 0 , sizeof(lazy));
    init(1, 1, N);
    
    scanf("%d", &M);
    for(int i=0; i<M; i++){
        int a,b,c,d;
        scanf("%d", &a);
        if(a==1){
            scanf("%d %d %d", &b, &c, &d);
            update(1, b, c , 1, N, d);
        }
        if(a==2){
            scanf("%d", &b);
            printf("%d\n", query(1, b, 1, N));
        }
    }
}