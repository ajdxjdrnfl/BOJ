#include <stdio.h>
#include <stdlib.h>
typedef struct _POINT{
    int x;
    int y;
}POINT;

POINT arr[1001];
int dp[1001][1001]; 
int re[1001][1001];

int police(int i, int j, int num, int N, int W){

    if(dp[i][j] != 0 ) return dp[i][j];
    if(num>W) return 0;
    
    int a, b; 
    if(i==0) a = abs(arr[num].y-1) + abs(arr[num].x-1) + police(num, j, num+1, N, W);
    else a = abs(arr[num].y- arr[i].y) + abs(arr[num].x - arr[i].x) + police(num, j, num+1, N, W);

    if(j==0) b = abs(arr[num].y-N) + abs(arr[num].x-N) + police(i, num, num+1, N, W);
    else b = abs(arr[num].y - arr[j].y) + abs(arr[num].x - arr[j].x) + police(i, num, num+1, N, W);
    
    if(a>b) re[i][j] = 2;
    else re[i][j] = 1;
    dp[i][j] = a>b?b:a;
    return dp[i][j];
}

int main(void){

    int N,W;
    scanf("%d %d", &N, &W);
    for(int i=1; i<=W; i++){
        scanf("%d %d", &arr[i].y, &arr[i].x);
    }
    dp[0][0] = 0;
    police(0, 0, 1, N, W);   
    printf("%d\n", dp[0][0]);
    int i=0, j=0, num=1;
    while(num<=W){
        if(re[i][j]==1){
            printf("1\n");
            i=num++;
        }
        else if(re[i][j]==2){
            printf("2\n");
            j=num++;
        }
    }
}