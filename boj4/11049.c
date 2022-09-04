#include <stdio.h>

int min(int a, int b){
    if(a<b) return a;
    return b;
}
int main(void){

    int N;
    scanf("%d", &N);
    int row[N], col[N];
    for(int i=0; i<N; i++){
        scanf("%d %d", &row[i], &col[i]);
    }
    
    int dp[N][N];
    int K[N][N];
    for(int i=0; i<N; i++){
        dp[i][i] = 0;
        K[i][i] = i;
        K[i][i+1] = i;
    }
    for(int i=1; i<N; i++){
        
        for(int j=0; j<N-i; j++){
               
            for(int k=K[j][j+i-1];  k<=K[j+1][j+i]; k++){
                if(k==K[j][j+i-1]) {
                    dp[j][j+i] =  dp[j][k]+dp[k+1][j+i] + row[j]*col[j+k]*col[j+i];
                    K[j][j+i] = k;
                }
                else if(dp[j][j+i] > dp[j][k]+dp[k+1][j+i] + row[j]*col[k]*col[j+i]){
                     dp[j][j+i] =  dp[j][k]+dp[k+1][j+i] + row[j]*col[k]*col[j+i];
                     K[j][j+i] = k;
                }
            }
        }
    }

    printf("%d\n", dp[0][N-1]);
}