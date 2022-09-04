#include <stdio.h>

typedef struct _POINT{
    long long x;
    long long y;
}POINT;

POINT p[4];

int  ccw(long long x1, long long y1, long long x2, long long y2, long long x3, long long y3){
    long long sum =  x1*y2 + x2*y3 + x3*y1 - (y1*x2 + y2*x3 + y3*x1);
    if(sum > 0) return 1;
    else if(sum ==0 ) return 0;
    else return -1;
}

void swap(POINT *a, POINT *b){
    long long temp_x, temp_y;
    temp_x = a->x;
    temp_y = a->y;
    a->x = b->x;
    a->y = b->y;
    b->x = temp_x;
    b->y = temp_y;
}

int small(POINT a, POINT b){
    if(a.x < b.x) return 1;
    else if(a.x == b.x && a.y < b.y) return 1;
    else return 0;
}

int fourLine(POINT a, POINT b, POINT c, POINT d){
    
    if(small(b, a)==1) swap(&a,&b);
    if(small(d,c)==1) swap(&c,&d);

    if(small(d,a)==1 || small(b,c)==1) return 1;
    else return 0;
}
int main(void){

    for(int i=0; i<4; i++){
        scanf("%lld %lld", &p[i].x, &p[i].y);
    }

    int a  = ccw(p[0].x, p[0].y, p[1].x, p[1].y, p[2].x, p[2].y) * ccw(p[0].x, p[0].y, p[1].x, p[1].y, p[3].x, p[3].y);
    int b   = ccw(p[2].x, p[2].y, p[3].x, p[3].y, p[0].x, p[0].y) * ccw(p[2].x, p[2].y, p[3].x, p[3].y, p[1].x, p[1].y);
    
    if(a==0 && b==0 && fourLine(p[0],p[1],p[2],p[3]) == 1) printf("0\n");
    else if(a<=0 && b<=0) printf("1\n");
    else printf("0\n");

    
}