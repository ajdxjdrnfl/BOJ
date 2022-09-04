#include <stdio.h>
#include <string.h>

#define LEFT 97
#define RIGHT 1031
int dp[2][1032][1032];

long long binomial(int n, int m, int index, int p){
    if(dp[index][n][m]!=-1) return dp[index][n][m];
    if(m==0 || n==m) return 1;
    long long ans ;
    ans = (binomial(n-1, m-1, index, p) + binomial(n-1, m, index, p))%p;
    dp[index][n][m] = ans;
    return ans;
}
long long lucas(long long n, long long m, int index, long long p){
    
    int vec1[100];
    int vec2[100];
    int top1=0, top2=0;
    long long res = 1;
    while(n){
        vec1[top1++] = n%p;
        n = n/p;
    }
    while(m){
        vec2[top2++] = m%p;
        m = m/p;
    }
    for(int i=0; i<top1; i++){
        int a,b;
        a = vec1[i];
        if(i<top2) b = vec2[i];
        else b=0;

        if(a<b) return 0;
        else res = (res*binomial(a,b, index ,p))%p; 
    }
    return res;
    
}

long long inverse(long long a, long long b, long long p){
    
    long long s1=1,s2=0,t1=0,t2=1;

    while(b){
        long long m =a%b;
        long long q =a/b;
        a = b;
        b = m;
        long long s = s1 - q*s2;
        long long t = t1 - q*t2;
        s1 = s2;
        t1 = t2;
        s2 = s;
        t2 = t;
    }

    return (s1%p+p)%p;
}

long long crt(long long a, long long m1, long long b, long long m2, long long M){
    long long ans = 0;

    ans = (ans+(m2*a*inverse(m2, m1, M)))%M;
    ans = (ans+(m1*b*inverse(m1, m2, M)))%M;
   
    
    return ans;
}


int main(void){

    int T;
    scanf("%d", &T);
    memset(dp, -1, sizeof(dp));
    while(T--){
        long long N,M;
        scanf("%lld %lld", &N, &M);
        if(N==0 && M==1){
            printf("1\n");
            continue;
        }
        if(M==1){
            printf("0\n");
            continue;
        }
        if(N<M-1){
            printf("0\n");
            continue;
        }
        long long left = lucas(N-1, M-2, 0, LEFT);
        long long right = lucas(N-1, M-2, 1, RIGHT);
        
        printf("%lld\n", crt(left, LEFT, right ,RIGHT , LEFT*RIGHT));
    }
}