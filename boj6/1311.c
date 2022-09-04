#include <stdio.h>

#define INF 200001
int arr[21][21];
int dp[21][1<<21];

int check(int bitmask, int index){
    if(( bitmask & (1<<(index-1)) )> 0) return 1;
    else return 0;
}

int add(int bitmask, int index){
    return (bitmask | (1<<(index-1)));
}

int min(int a, int b){
    return a<b?a:b;
}
int work(int index, int bitmask, int N){
    
    if(index>N) return 0;
    if(dp[index][bitmask]!=0) return dp[index][bitmask];

    int shortest =  INF;

    for(int i=1; i<=N; i++){
        if(check(bitmask, i)==1) continue;
        else{
            shortest = min(shortest, arr[index][i] + work(index+1, add(bitmask, i), N));
        }
    }
    dp[index][bitmask] = shortest;
    return dp[index][bitmask]; 
}


int main(void){

    int N;
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            scanf("%d", &arr[i][j]);
        }
    }

    work(1, 0, N);
    printf("%d\n", dp[1][0]);

}