#include <stdio.h>

void egcd(long long a, long long b){
    long long s1=1,s2=0,t1=0, t2=1;
    long long temp_a = a , temp_b = b;
    while(b){
        long long temp = a%b;
        long long q = a/b;
        long long s,t;
        s = s1 - q*s2;
        t = t1 - q*t2;
        s1 = s2;
        t1 = t2;
        t2 = t;
        s2 = s;
        a = b;
        b = temp;
        
    }

    if(a!=1) {
        printf("IMPOSSIBLE\n");
        return;
    }
    
    s1 =  ((s1%temp_b) + temp_b)%temp_b;
    if(s1>1e9) printf("IMPOSSIBLE\n");
    else printf("%lld\n", s1);
    

}
int main(void){
    int T;
    scanf("%d", &T);
    while(T--){
    
        long long K,C;
        scanf("%lld %lld", &K, &C);
        
        if(C==1) {
            if(K+1>1e9) printf("IMPOSSIBLE\n");
            else printf("%lld\n", K+1);
            continue;
        }
        if(K==1) {
            printf("1\n");
            continue;
        }
        egcd(C,K);
    }
}
