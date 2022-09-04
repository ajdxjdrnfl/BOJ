#include <stdio.h>
#include <string.h>

#define MAX 100001
int dp[10001][10];
char before[10002], after[10002];


int min(int a, int b){
    return a<b?a:b;
}
int screw(int index, int acc, int N){
    
    if(index==N) return 0;
    if(dp[index][acc]!=MAX) return dp[index][acc];
    
    int left = (after[index] - before[index] - acc + 20) %10;
    int right = 10-left;
    dp[index][acc]= min(screw(index+1, (acc+left)%10 , N) + left, screw(index+1, acc, N)+right);
    return dp[index][acc];  
}
int main(void){

    int N;
   
    scanf("%d", &N);
    scanf("%s %s", before, after);
    for(int i=0; i<N; i++){
        for(int j=0; j<10; j++){
            dp[i][j] = MAX; 
        }
    }
    for(int i=0; i<N; i++){
        before[i] -= '0';
        after[i] -= '0';
    }
   
    printf("%d\n", screw(0,  0, N));
    
}