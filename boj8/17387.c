#include <stdio.h>

typedef struct _POINT{
    long long x;
    long long y;
}POINT;

void swap(POINT *a, POINT *b){
    POINT temp = *a;
    *a = *b;
    *b = temp;
}

long long ccw(POINT a, POINT b, POINT c){
    long long ans = ((a.x*b.y+b.x*c.y+c.x*a.y) - (b.x*a.y+c.x*b.y+a.x*c.y));
    if(ans<0) return -1;
    else if(ans>0) return 1;
    else return 0;
}

int small(POINT a, POINT b){
    if(a.x<b.x) return 1;
    else if(a.x==b.x && a.y<b.y) return 1;
    else if(a.x==b.x && a.y==b.y) return 1;
    else return 0;
}
long long isCross(POINT p1, POINT p2, POINT p3, POINT p4){
   long long abc = ccw(p1, p2, p3);
   long long abd = ccw(p1, p2, p4);
   long long cda = ccw(p3,p4,p1);
   long long cdb = ccw(p3,p4,p2);

    if((abc*abd==0) && (cda*cdb==0)) {
        if(small(p2,p1)==1) swap(&p1,&p2);
        if(small(p4,p3)==1) swap(&p3,&p4);
        return (small(p1,p4)==1 && small(p3, p2)==1);
    }  
    
    return ( (abc*abd<=0) && (cda*cdb<=0) );
}
int main(void){
    POINT p1,p2,p3,p4;
    scanf("%lld %lld", &p1.x, &p1.y);
    scanf("%lld %lld", &p2.x, &p2.y);
    scanf("%lld %lld", &p3.x, &p3.y);
    scanf("%lld %lld", &p4.x, &p4.y);
    
    if(isCross(p1,p2,p3,p4)) printf("1\n");
    else printf("0\n");
}