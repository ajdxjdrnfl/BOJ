#include <stdio.h>

int r[1001], g[1001], b[1001];
int dp[3][1001][3];

#define R 0
#define G 1
#define B 2
#define INF 1000001

int min(int a, int b){
    return a<b?a:b;
}
int rgb(int index, int color, int N, int preColor){

    if(N < index) return 0;
    if(N == index){
        if(preColor == color) return INF;
      
    }
    if(dp[preColor][index][color]!=0) return dp[preColor][index][color];

    int shortest =INF;
    
    if(color == R){
    shortest = min(shortest, r[index] + rgb(index+1, G, N, preColor));
    shortest  = min(shortest , r[index] + rgb(index+1, B, N, preColor));
    
    }
    if(color == G){
        shortest = min(shortest, g[index] + rgb(index+1, R, N, preColor));
        shortest = min(shortest, g[index] + rgb(index+1, B, N, preColor));
    }
    if(color == B){
        shortest = min(shortest, b[index] + rgb(index+1, R, N, preColor));
        shortest = min(shortest, b[index] + rgb(index+1, G, N, preColor));
    }
    dp[preColor][index][color] = shortest;
        
    return shortest;
}
int main(void){

    int N;
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
            scanf("%d %d %d", &r[i], &g[i], &b[i]);
    }
    rgb(1, R, N, R);
    rgb(1, G, N, G);
    rgb(1, B, N, B);
    printf("%d", min(dp[R][1][R], min(dp[G][1][G], dp[B][1][B])));
}