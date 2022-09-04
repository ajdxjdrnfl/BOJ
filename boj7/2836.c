#include <stdio.h>
#include <stdlib.h>

typedef struct _POINT{
    long long x;
    long long y;
}POINT;

POINT p[300001];

int comp(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    if(pa.x<pb.x) return 1;
    else if(pa.x>pb.x) return -1;
    else{
        if(pa.y<pb.y) return 1;
        else if(pa.y>pb.y) return -1;
        return 0;
    }
}

int main(void){
    int N,M;
    long long result = 0;
    scanf("%d %d", &N, &M);
    int size = 0;
    for(int i=0; i<N; i++){
        long long x,y;
        scanf("%lld %lld", &x, &y);
        if(y<x){
            p[size].x = x;
            p[size++].y = y;
        }
    }
    qsort(p, size, sizeof(POINT), comp);
    
    long long front = p[0].x;
    long long rear = p[0].y; 
   
    for(int i=1; i<size; i++){
        if(rear < p[i].x) {
            if(rear > p[i].y) rear = p[i].y;
        } 
        else{
            result += (front-rear);
            front = p[i].x;
            rear = p[i].y;
        }
    }
    result += (front-rear);
    printf("%lld\n", 2*result+M);
}