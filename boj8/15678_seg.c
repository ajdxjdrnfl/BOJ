#include <stdio.h>

long long dp[100001];
long long tree[400004];
int N,D;
long long max(long long a, long long b){
    return a>b?a:b;
}
long long find(int node, int rear, int front, int start, int end){
    if(rear>end || front < start) return -1000000001;
    if(rear <= start && end <=front) return tree[node];

    int mid = (start+end)/2;
    return max(find(node*2, rear, front, start, mid), find(node*2+1, rear, front, mid+1, end));
}

void update(int node, int index, int start, int end){
    if(index<start || index>end) return ;
    if(start==end){
        tree[node] = dp[index];
        return ;
    }
    int mid=(start+end)/2;
    update(node*2, index, start, mid);
    update(node*2+1, index, mid+1, end);
    tree[node] = max(tree[node*2], tree[node*2+1]);
}
int main(void){
    
    scanf("%d %d", &N, &D);
    

    for(int i=1; i<=N; i++){
        long long bridge;
        scanf("%lld", &bridge);
        dp[i] = max(bridge, bridge +  find(1, max(1, i-D), max(1, i-1), 1, N));
        update(1, i, 1, N);
    }
    long long ans = dp[1];
    for(int i=1; i<=N; i++){
        ans = max(ans, dp[i]);
    }
    printf("%lld\n", ans);
}