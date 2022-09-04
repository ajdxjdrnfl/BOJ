#include <stdio.h>

long long arr[1000001];
              

int logs(int N){
    if(N/2!=0) return 1+logs(N/2);
    else return 0;
}

long long init(long long *tree, int index, int start, int end){
    
    if(start > end) return 0;
    if(start==end){
        tree[index] = arr[start];
        return tree[index];
    }
 
    int mid = (start+end)/2;
    long long left = init(tree, index*2, start, mid);
    long long right = init(tree, index*2+1, mid+1, end);
    tree[index] = left+right;
    return tree[index];
}

void update(long long *tree, int node, int index, int start, int end, long long value){
    if(index<start || index>end) return;
    tree[node] += value;
    if(start!=end){
        int mid = (start+end)/2;
        update(tree, node*2, index, start, mid, value);
        update(tree, node*2+1, index, mid+1, end, value);
    }


}

long long sum(long long *tree, int node,int rear, int front, int start, int end){
    
    if(rear>end || front<start) return 0;
    if(rear <= start && front >= end) return tree[node];
    int mid = (start+end)/2;
    
    return sum(tree, node*2, rear, front, start, mid) + sum(tree, node*2+1, rear, front, mid+1, end);
}
int main(void){
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    int h = logs(N);
    if(N%2!=0) h++;
    int tree_size = 1 << (h+1);
    for(int i=1; i<=N; i++){
        scanf("%lld", &arr[i]);
    }
    long long tree[tree_size+1];
    
    init(tree, 1, 1, N);

    for(int i=0; i<M+K; i++){
        int a;
        scanf("%d", &a);
        if(a==1){
            int b;
            long long c;
            scanf("%d %lld", &b, &c);
            update(tree, 1, b, 1, N, c-arr[b]);
            arr[b] = c;
        }
        else if(a==2){
            int b,c;
            scanf("%d %d", &b, &c);
            printf("%lld\n",sum(tree, 1, b, c, 1, N));
        }
    }
}