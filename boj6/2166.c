#include <stdio.h>
#include <math.h>

typedef struct _POINT{
    double x;
    double y;
}POINT;

double triangle(POINT a, POINT b, POINT c){
    return (a.x*b.y +b.x*c.y + c.x*a.y - a.y*b.x - b.y*c.x - c.y*a.x);
}

double absd(double a){
    return a>=0?a:-a;
}
POINT point[10001];

int main(void){
    int N;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%lf %lf", &point[i].x, &point[i].y);
    }
    int fix = 0;
    int last = 1;
    double sum =0;
    for(int i=2; i<N; i++){
        sum += triangle(point[fix], point[last], point[i]);
        last = i;
    }

    printf("%.1lf\n", absd(sum)*0.5);
    
}