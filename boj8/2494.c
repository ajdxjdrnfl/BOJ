#include <stdio.h>
#include <string.h>

#define MAX 100001
int dp[10001][10];
int track[10001][10];
char before[10002], after[10002];


void printTrack(int index, int acc, int N){
    if(index==N) return;
    printf("%d %d\n", index+1, track[index][acc]);
    if(track[index][acc] >= 0){
    printTrack(index+1, (acc+track[index][acc]+10)%10, N);
    }
    else{
        printTrack(index+1, acc, N);
    }
}
int screw(int index, int acc, int N){
    
    if(index==N) return 0;
    if(dp[index][acc]!=MAX) return dp[index][acc];
    
    int left = (after[index] - before[index] - acc + 20) %10;
    int right = 10-left;
    int temp_left = screw(index+1, (acc+left)%10 , N) + left;
    int temp_right = screw(index+1, acc, N)+right;
    
    if(temp_left < temp_right){
        dp[index][acc] = temp_left;
        track[index][acc] = left;
    }
    else{
        dp[index][acc] = temp_right;
        track[index][acc] = left-10;
    }
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
    printTrack(0, 0, N);
}