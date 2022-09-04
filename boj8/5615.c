#include <stdio.h>

unsigned long long a[12] = {2,3,5,7,11,13,17,19,23,29,31,37};

unsigned long long POWER(unsigned long long x, unsigned long long y, unsigned long long m){
   unsigned long long result = 1;
    x = x%m;
    while(y){
        if(y%2) result = (x*result)%m;
        y = y/2;
        x = (x*x)%m;

    }
    return result;
}
int miller(unsigned long long N){


    unsigned long long r=0;
    unsigned long long d = N-1;
    
    while(d%2==0){
        r++;
        d = d/2;
    }
    
    for(int i=0; i<12; i++){
        if(a[i]==N) return 1;
        unsigned long long ad = POWER(a[i], d, N);
        
        if(ad==1 || ad==N-1) continue;
        if(r==1) return 0;
        for(int j=1; j<r; j++){
            ad = (ad*ad)%N;
            if(ad==N-1) break;
            if(j==r-1)  {
                return 0;
            }
        }

    }
    
    return 1;

}
int main(void){

    
    int t;
    scanf("%d", &t);
    int cnt = 0;
    while(t--){
        unsigned long long N;
        scanf("%llu", &N);
        if(miller(2*N+1)) {
            cnt++;
        }
    }
    printf("%d\n", cnt);
}