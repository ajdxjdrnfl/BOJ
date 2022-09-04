#include <stdio.h>

long long arr[1000001];

int logs(int N){
    if(N/2!=0) return 1+logs(N/2);
    else return 0;
}

long long init(long long *tree, int node, int start, int end){
    if(start==end){
        tree[node] = arr[start];
        return tree[node];
    }
    int mid = (start+end)/2;
    tree[node] = (init(tree, node*2, start, mid) * init(tree, node*2+1, mid+1, end))% 1000000007;
    return tree[node];
}

long long update(long long *tree, int node, int index, int start, int end, long long value){
    
    if(start> index || end < index) return tree[node];
    if(start==end) {
        tree[node] = value;
        return tree[node];
    }

    int mid = (start+end)/2;
    tree[node] = (update(tree, node*2, index, start, mid, value) * update(tree, node*2+1, index, mid+1, end, value))% 1000000007;
    return tree[node];
}

long long mul(long long *tree, int node, int start, int end, int rear, int front){

    if(start>front || end < rear ) return 1;
    if(rear<=start && end<=front) return tree[node];
    int mid = (start+end)/2;
    return (mul(tree, node*2, start, mid, rear, front) * mul(tree, node*2+1, mid+1, end, rear, front))% 1000000007;
}

int main(void){
    int N,M,K;
    scanf("%d %d %d", &N, &M, &K);
    for(int i=1; i<=N; i++){
        scanf("%lld", &arr[i]);
    }
    int h = logs(N)+1;
    int tree_size = 1 <<(h+1);
    long long tree[tree_size+1];
    init(tree, 1, 1, N);
    for(int i=0; i<M+K; i++){
        int a;
        scanf("%d", &a);
        if(a==1){
            int b;
            long long c;
            scanf("%d %lld", &b, &c);
            update(tree, 1, b, 1, N, c);
            arr[b] = c;
        }
        if(a==2){
            int b,c;
            scanf("%d %d", &b, &c);
            printf("%lld\n", mul(tree, 1, 1, N, b, c));
        }
    }
}