#include <stdio.h>
#include <string.h>

char arr[16][51];
int tenMod[51];
int charMod[16];
int charLen[16];
long long dp[100][1<<15];

int check(int bitmask, int i){
    if((bitmask & (1<<(i-1)))>0) return 1;
    else return 0;
}

int add(int bitmask, int i){
    return (bitmask | (1<<(i-1)));
}

long long park(int mod, int bitmask, int N, int K){
    
    if(bitmask+1==(1<<N)){
        if(mod==0) return 1;
        else return 0;
    }
    if(dp[mod][bitmask] != -1) return dp[mod][bitmask];

    long long result =0;

    for(int i=1; i<=N; i++){
        if(check(bitmask, i)==1) continue;
        result += park( (mod*tenMod[charLen[i]]+ charMod[i])%K, add(bitmask, i), N, K);
    }
    dp[mod][bitmask] = result;

    return dp[mod][bitmask];
}

long long GCD(long long a, long long b){
    long long temp, n;
    if(a<b){
        temp = a;
        a=b;
        b=temp;
    }

    while(b!=0){
        n = a%b;
        a =b;
        b =n;
    }
    return a;
}
int main(void){

    int N;
    long long all=1;
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        scanf("%s",arr[i]);
        all *=i; 
    }
    int K;
    scanf("%d", &K);

    tenMod[0] = 1%K;

    for(int i=1; i<51; i++){
        tenMod[i] = (tenMod[i-1]*10)%K;
    }
    
    for(int i=1; i<=N; i++){
        int len = strlen(arr[i]);
        charLen[i] = len;
        int mod=0;
        for(int j=0 ; j<len; j++){
            mod = (mod + (((arr[i][j]-'0')*tenMod[len-j-1]%K)))%K;
        }
        charMod[i] = mod;
    }
    long long result =0;
    memset(dp, -1, sizeof(dp));
    for(int i=1; i<=N; i++){
        result+=park(charMod[i], add(0, i), N,K);
    }    
    long long gcd = GCD(all, result);
  
    printf("%lld/%lld\n", result/gcd, all/gcd);
}