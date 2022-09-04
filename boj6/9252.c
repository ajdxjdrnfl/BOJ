#include <stdio.h>
#include <string.h>
char lcs[2][1001];
int dp[1001][1001];
int re[1001][1001];

#define ONE 1
#define TWO 2
#define THREE 3

void printLCS(int i, int j){
    
    if(i<0 || j<0) return;
    if(re[i][j] == ONE) {
        printLCS(i-1, j-1);
        printf("%c", lcs[0][j]);
    }
    if(re[i][j] == TWO) printLCS(i, j-1);
    if(re[i][j] == THREE) printLCS(i-1, j);
}
int main(void){

    
    scanf("%s", lcs[0]);
    scanf("%s", lcs[1]);
    
    int zero_len;
    int one_len;

    zero_len = strlen(lcs[0]);
    one_len = strlen(lcs[1]);
    for(int i=0; i<one_len; i++){
        
        for(int j=0; j<zero_len; j++){
            int result=0;
            if(lcs[0][j] == lcs[1][i]){
                if(i-1>=0 && j-1>=0) result = dp[i-1][j-1] + 1;
                else result = 1;
                re[i][j] = ONE;
            }
            if(j-1>=0 && result < dp[i][j-1]) {
                result = dp[i][j-1];
                re[i][j] = TWO;
            }
            if(i-1>=0 && result < dp[i-1][j]) {
                result = dp[i-1][j];
                re[i][j] = THREE;
            }
            dp[i][j] = result;
            

        }
    }
    printf("%d\n", dp[one_len-1][zero_len-1]);
    printLCS(one_len-1, zero_len-1);
    printf("\n");
}