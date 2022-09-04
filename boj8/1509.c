#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char str[2501];
int dp[2502];
int pby[2501][2501];

int pel(int start, int end){
    if(start>=end) return 1;
    if(pby[start][end]!=-1) return pby[start][end];
    
    if(str[start]==str[end]) {
        pby[start][end] = pel(start+1, end-1);
        return pby[start][end];
    }
    else return 0;
}
int min(int a, int b){
    return a<b?a:b;
}
int main(void){
    
   

    scanf("%s", str);
    memset(dp, -1, sizeof(dp));
    memset(pby, -1, sizeof(pby));
     dp[0] = 1;
    for(int i=1; i<strlen(str); i++){
        dp[i] = dp[i-1] + 1;
        for(int j=0; j<i; j++){
            if(pel(j, i)==1) {
                if(j==0) dp[i] = 1;
                else dp[i] =  min(dp[i] , dp[j-1]+1);
            }
        }
    }
    
    printf("%d\n", dp[strlen(str)-1]);
}