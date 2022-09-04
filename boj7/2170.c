#include <stdio.h>
#include <stdlib.h>

typedef struct _POINT{
    int x;
    int y;
}POINT;

POINT p[1000001];

int comp(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    if(pa.x<pb.x) return -1;
    else if(pa.x>pb.x) return 1;
    else{
        if(pa.y<pb.y) return -1;
        else if(pa.y>pb.y) return 1;
        return 0;
    }
}
int main(void){
    int N;
    long long result=0;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d %d", &p[i].x, &p[i].y);
    }
    qsort(p, N, sizeof(POINT), comp);
    
    int x=p[0].x;
    int y=p[0].y;
    result += (p[0].y-p[0].x);
    for(int i=1; i<N; i++){
        if(y<=p[i].x){
            x = p[i].x;
            y = p[i].y;
            result += (y-x);
        }
        else if(p[i].y<=y) continue;
        else{
            result += (p[i].y-y);
            y = p[i].y;
           
        }
    }
    printf("%lld\n", result);
}