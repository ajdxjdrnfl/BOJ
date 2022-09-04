#include <stdio.h>

long long x[4], y[4];

long long ccw(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){
    return x1*y2 + x2*y3 + x3*y1 - (y1*x2 + y2*x3 + y3*x1) > 0 ? 1 : -1;
}


int main(void){

    for(int i=0; i<4; i++){
        scanf("%lld %lld", &x[i], &y[i]);
    }

    long long a  = ccw(x[0], y[0], x[1], y[1], x[2], y[2]) * ccw(x[0], y[0], x[1], y[1], x[3], y[3]);
    long long b   = ccw(x[2], y[2], x[3], y[3], x[0], y[0]) * ccw(x[2], y[2], x[3], y[3], x[1], y[1]);
    if(a<=0 && b<=0) printf("1\n");
    else printf("0\n");

    
}