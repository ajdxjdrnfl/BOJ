#include <stdio.h>

int main(void){
    int N,M;
    long long large_tree;
    long long ans = -1;
    scanf("%d %d", &N, &M);

    long long tree[N];
    for(int i=0; i<N; i++){
        scanf("%lld", &tree[i]);
        if(i==0) large_tree = tree[i];
        else if(large_tree < tree[i]) large_tree = tree[i];
    }

    long long low = 0;
    long long high = large_tree;
    while(low<=high){
        long long mid = (low+high)/2;
        long long temp = 0;
        for(int i=0; i<N; i++){
            if(tree[i]>mid) temp = temp + tree[i] - mid;
        }

        if(temp>=M){
            low = mid+1;
            if(ans<mid) ans = mid;
        }
        else if(temp<M) high = mid-1;
    }
    printf("%lld\n", ans);

    
}