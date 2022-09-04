#include <stdio.h>

#define INF 10000001

int arr[101][101][101];
int re[101][101][101];

void floyd(int n){

    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                if(arr[i-1][j][k] <= arr[i-1][j][i] + arr[i-1][i][k]){
                    arr[i][j][k] = arr[i-1][j][k];
                    re[i][j][k] = re[i-1][j][k];
                }
                else{
                    arr[i][j][k] = arr[i-1][j][i] + arr[i-1][i][k];
                    re[i][j][k] = re[i-1][i][k];
                    }
                    
            }
        }
    }
}

void printFloyd(int num, int i, int j, int result){
    if(re[num][i][j]==0) printf("0");
    else if(re[num][i][j]==i){
        printf("%d %d %d ", result+1, i, j);
    }
    else{
        printFloyd(num, i, re[num][i][j], result+1);
        printf("%d ",j);
    }
 
}
int main(void){
    int n,m;
    scanf("%d %d", &n, &m);
    for(int i=0; i<=n; i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                if(j==k) {
                    arr[i][j][k] = 0;
                }
                else arr[i][j][k] = INF;
            }
        }
    }
    for(int i=0; i<m; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if(arr[0][a][b] == 0 || arr[0][a][b] > c) {
            arr[0][a][b] = c;
            re[0][a][b] = a;
        }
    }
    floyd(n);
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            if(arr[n][i][j]<INF) printf("%d ", arr[n][i][j]);
            else printf("0 ");
        }
        printf("\n");
    }
   
    
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            printFloyd(n, i,j, 1);
            printf("\n");
        }
    }
}