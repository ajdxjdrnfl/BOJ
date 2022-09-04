#include <stdio.h>

int arr[501][501];
int dp[501][501];
int M,N;
int ans=0;
int map(int i, int j)
{   if(dp[i][j] == -1) return 0;
    if(dp[i][j] != 0) return dp[i][j];
    if(i==M-1 && j==N-1) {
        return 1;
    }
    int cnt=0;
    if(j+1<N && arr[i][j+1]<arr[i][j]) cnt+=map(i, j+1);

    if(i+1<M && arr[i+1][j]<arr[i][j]) cnt+=map(i+1, j);

    if(j-1>=0 && arr[i][j-1]<arr[i][j]) cnt+=map(i, j-1);

    if(i-1>=0 && arr[i-1][j]<arr[i][j]) cnt+=map(i-1, j);

    if(cnt==0) {
        dp[i][j]=-1;
        return 0;
    }
    else {
        dp[i][j] = cnt;

    return dp[i][j];
    }

}
int main(void){

    
    scanf("%d %d", &M, &N);
    
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            scanf("%d", &arr[i][j]);
        }
    }

    int ans = map(0, 0);
    printf("%d\n", ans);
}