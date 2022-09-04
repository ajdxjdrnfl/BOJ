#include <stdio.h>

int dp[2001][2001];
int felrom(int *num, int start, int end){
    if(dp[start][end]==1) return 1;
    if(start>=end) return 1;
    if(num[start]==num[end]){
        dp[start][end]= felrom(num, start+1, end-1);
        return dp[start][end];
    }
    return 0;
}
int main(void){
    int N;
    scanf("%d", &N);
    int num[N+1];
    for(int i=1; i<=N; i++){
        scanf("%d", &num[i]);
    }
    
    int M;
    scanf("%d", &M);
    while(M--){
        int S,E;
        scanf("%d %d", &S, &E);
        printf("%d\n", felrom(num, S,E));
    }
}