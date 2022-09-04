#include <stdio.h>

int dp[1000001];
int re[1000001];

int min(int a, int b){
    return a>b?b:a;
}
int maketo(int N){
    if(dp[N]!=0) return dp[N];
    if(N==1) return 0; 

    int a=1000001,b=1000001,c=1000001;
    if(N%3==0) a = maketo(N/3);
    if(N%2==0) b = maketo(N/2);
    c = maketo(N-1);
    
   
    int shortest = min(a,min(b,c));
    if(a==shortest) {
        dp[N] = a+1;
        re[N] = N/3;
    }
    else if(b==shortest){
        dp[N] = b+1;
        re[N] = N/2;
    }
    else if(c==shortest){
        dp[N] = c+1;
        re[N] = N-1;
    }
    return dp[N];
}
int main(void){

    int N;
    scanf("%d", &N);
    dp[1] = 0;
    re[1] = 0;
    maketo(N);

    printf("%d\n", dp[N]);
    printf("%d ", N);
    for(int i=N; ; i=re[i]){
        if(re[i]==0) break;
        printf("%d ", re[i]);
    }
    printf("\n");
}