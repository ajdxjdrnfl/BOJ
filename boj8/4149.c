#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef __int128_t ull;

ull stack[100];
int top=0;

ull Base[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

int comp(const void*a, const void*b){
    ull pa = *(ull*)a;
    ull pb = *(ull*)b;
    if(pa<pb) return -1;
    if(pa>pb) return 1;
    return 0;
}
ull gcd(ull a, ull b){
    
    while(b){
        ull temp = b;
        b = a%b;
        a = temp;
    }
    return a;
}

ull f(ull x, ull c, ull mod){
    return ((x*x)%mod+c)%mod;
}

ull absU(ull x, ull y){
    if(x>y) return x-y;
    else return y-x;
}
ull POWER(ull x, ull n, ull mod){
    ull res = 1;
    x = x%mod;
    while(n){
        if(n%2) res = (res*x)%mod;
        n = n/2;
        x = (x*x)%mod;
    }
    return res;
}
int miller(ull N, ull a){
    int r=0;
    ull d = N-1;
    
    if(a==N) return 1;

    while(d%2==0){
        r++;
        d = d/2;
    } 
    ull ad = POWER(a ,d, N);

    if(ad==N-1 || ad==1) return 1;
    for(int i=0; i<r-1; i++){
        ad  = (ad*ad)%N;
        if(ad==N-1) return 1;
    }

    return 0;
}

int isPrime(ull N){

    for(int i=0; i<12; i++){
        if(!miller(N, Base[i])) return 0;
    }
    return 1;
}

int rho(ull N){
    
    
    if(N==1) return 1;
    if(N%2==0){
        stack[top++] = 2;
        rho(N/2);
        return 1;
    }
    if(isPrime(N)) {
        stack[top++] = N;
        return 1;
    }
    
    ull x,y,c,g=N;

    while(1){
        if(g==N){
            x = rand()%(N-2)+1;
            y = x;
            c = rand()%10+1;
            g = 1;
    
        }
       
        x = f(x, c, N);
        y = f(f(y, c, N),c, N);
        g = gcd(absU(x,y), N);
        if(g!=1 && g!=N) break;
    }
    
        rho(N/g);
        rho(g);
        return 1;

}

int main(void){

    unsigned long long N;
    scanf("%llu", &N);
    srand(time(NULL));
    rho(N); 
    qsort(stack, top, sizeof(ull), comp);
    for(int i=0; i<top; i++){
        printf("%llu\n", (unsigned long long)stack[i]);
    }
} 
