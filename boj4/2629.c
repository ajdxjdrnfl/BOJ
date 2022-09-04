#include <stdio.h>
int dp[31][40001];
int yangpal(int *weight, int index, int N,int check){
    if(check==0) return 1;
    if(index==N) return -1;
    if(dp[index][check]==1) return 1;
    if(dp[index][check]==-1) return -1;
    
    
    
    
    int left = yangpal(weight, index+1, N, check-weight[index]);
    int mid = yangpal(weight, index+1, N, check);
    int right = yangpal(weight, index+1, N, check+weight[index]);

    if(left>0 || mid > 0 || right >0) dp[index][check] = 1;
    else dp[index][check]=-1;

    return dp[index][check];
}

int main(void){
    int N;
    scanf("%d", &N);
    int weight[N];
    for(int i=0; i<N; i++){
        scanf("%d",&weight[i]);
    }
    int M;
    scanf("%d", &M);
    while(M--){
        int check;
        scanf("%d", &check);
        yangpal(weight, 0, N, check);
        if(dp[0][check] == 1) printf("Y ");
        else printf("N ");
    }

    printf("\n");
}