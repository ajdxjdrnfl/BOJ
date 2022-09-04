#include <stdio.h>

int main(void){
    char a[1001];
    char b[1001];
    int dp[1001][1001]={0};
   
    int a_len=0, b_len=0, largest;
    scanf("%s", a);
    scanf("%s", b);
    for(int i=0; ;i++){
        if(a[i]!='\0') a_len++;
        else break;
    }

    for(int i=0; ; i++){
        if(b[i]!='\0') b_len++;
        else break;

    }
    
    for(int i=1; i<=a_len; i++){
        
        for(int j=1; j<=b_len;j++){
            if(a[i-1] == b[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
            }
            else{
                if(dp[i-1][j]<dp[i][j-1]) dp[i][j] = dp[i][j-1];
                else dp[i][j] = dp[i-1][j];
            }

        } 
    }
    
    printf("%d", dp[a_len][b_len]);
}