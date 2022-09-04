#include <stdio.h>
#include <string.h>

#define INF 10000001
int D[101][101][101];

int min(int a, int b){
    return a<b?a:b;
}
int floyd(int n, int K){
    for(int i=1; i<=K; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                D[i][j][k] = min(D[i-1][j][k], D[i-1][j][i] + D[i-1][i][k]);
            }
        }
    }
}
int main(void){
    int n,m;
    scanf("%d", &n);
    scanf("%d", &m);
    for(int i=0; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                if(j==k) D[i][j][k]=0;
                else D[i][j][k] =INF;
            }
        }
    }
    for(int i=0; i<m; i++){
        int a,b,c;
        scanf("%d %d %d", &a, &b, &c);
        if(D[0][a][b]>c) D[0][a]
        [b]=c;
    }
    
    floyd(n,n);
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(D[n][i][j] != INF) printf("%d ",D[n][i][j]);
            else printf("%d ",0);
        }
        printf("\n");
    }
}