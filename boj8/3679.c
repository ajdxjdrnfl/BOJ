#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _POINT{
    long long x;
    long long y;
    int index;
}POINT;

POINT p[2001];

int ccw(POINT a, POINT b, POINT c){
    long long ans = (a.x*b.y+b.x*c.y+c.x*a.y) - (b.x*a.y+c.x*b.y+a.x*c.y);
    if(ans>0) return 1;
    else if(ans<0) return -1;
    else return 0;
}
int comp1(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;

    if(pa.y<pb.y) return -1;
    else if(pa.y>pb.y) return 1;
    else{
        if(pa.x<pb.x) return -1;
        else if(pa.x>pb.x) return 1;
        else return 0;
    }
}

long long dist(POINT a, POINT b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
int comp2(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    
    int cw = ccw(p[0], pa, pb);
    if(cw>0) return -1;
    else if(cw<0) return 1;
    else{
        if(dist(p[0],pa) < dist(p[0],pb)) return -1;
        else return 1;
    }
}
void swap(int i, int j){
    POINT temp;
    temp = p[i];
    p[i] = p[j];
    p[j] = temp;
}
int main(void){

    int c;
    scanf("%d", &c);
    while(c--){
        int n;
        
        scanf("%d", &n);
        memset(p, 0, sizeof(p));
        for(int i=0; i<n; i++){
            scanf("%lld %lld", &p[i].x, &p[i].y);
            p[i].index = i;
        }
        qsort(p, n, sizeof(POINT), comp1);
        qsort(&p[1], n-1, sizeof(POINT), comp2);
        int index = n-1;
        for(int i=index; i>=1; i--){
            if(ccw(p[0], p[i], p[i-1])==0) index--;
            else break;
        }
        if(index!=n-1){
            int i = index;
            int j = n-1;
            int k = 0;
            while(i+k<=j-k){
                swap(i+k,j-k);
                k++;
            }
        }
        for(int i=0; i<n; i++){
            printf("%d ", p[i].index);
        }
        printf("\n");
    }
}