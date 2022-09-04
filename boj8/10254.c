#include <stdio.h>
#include <stdlib.h>
typedef struct _POINT{
    long long x;
    long long y;
    long long rel_x;
    long long rel_y;
}POINT;



int comp1(const void *a, const void *b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    if(pa.y<pb.y) return -1;
    if(pa.y>pb.y) return 1;
    else{
        if(pa.x<pb.x) return -1;
        if(pa.x>pb.x) return 1;
        return 0;
    }
}

int comp2(const void*a , const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    if(pa.rel_y*pb.rel_x < pb.rel_y*pa.rel_x) return -1;
    if(pa.rel_y*pb.rel_x > pb.rel_y*pa.rel_x) return 1;
    else{
        if(pa.y<pb.y) return -1;
        if(pa.y>pb.y) return 1;
        else{
            if(pa.x<pb.x) return -1;
            if(pa.x>pb.x) return 1;
            return 0;
    }
    }
}

long long ccw(POINT a, POINT b, POINT c){
    return ((a.x*b.y+b.x*c.y+c.x*a.y) - (b.x*a.y+c.x*b.y+a.x*c.y));
}

long long ccw2(POINT a, POINT b, POINT c, POINT d){
    long long x1 = b.x - a.x;
    long long x2 = d.x - c.x;
    long long y1 = b.y - a.y;
    long long y2=  d.y - c.y;

    return (x1*y2 - x2*y1);
}

long long distance(POINT a, POINT b){
    return (b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y);
}
int main(void){

    int T;
    scanf("%d", &T);
    while(T--){
        int stack[200001];
        int top=-1;
        int N;
        POINT p[200001];
        scanf("%d", &N);
        
        
        for(int i=0; i<N; i++){
            scanf("%lld %lld", &p[i].x, &p[i].y);
        }
        if(N==2){
            printf("%lld %lld %lld %lld\n", p[0].x, p[0].y, p[1].x, p[1].y);
            continue;
        }
        
        qsort(p, N, sizeof(POINT), comp1);
        for(int i=0; i<N; i++){
            p[i].rel_x = p[i].x - p[0].x;
            p[i].rel_y = p[i].y - p[0].y;
        }
        qsort(&p[1], N-1, sizeof(POINT), comp2);
        stack[++top] = 0;
        stack[++top] = 1;
        int i = 2;
        while(i<N){
        
        if(top>=1){
            
        int b = stack[top--];
        int a = stack[top--];
        int c = i;
        
        if(ccw(p[b], p[c], p[a])>0){
            stack[++top] = a;
            stack[++top] = b;
            stack[++top] = c;
            i++;
        }
        else if(ccw(p[b], p[c], p[a])==0){
            stack[++top] = a;
            stack[++top] = c;
            i++;
        }
        else{
            stack[++top] = a;
        }
        }

        else stack[++top] = i++;
        
    }
        
        i = 1;
        long long ans=-1;
        int ans1= 0;
        int ans2= 1;
        int size = top+1;
        
        for(int j=0; j<size-1; j++){
            while(((i+1)%size)!=j && ccw2(p[stack[j]], p[stack[(j+1)%size]], p[stack[i%size]], p[stack[(i+1)%size]])>0 ){
                if(ans<distance(p[stack[j]], p[stack[i%size]])){
                    ans = distance(p[stack[j]], p[stack[i%size]]);
                    ans1 = j;
                    ans2 = i%size;
                }   
                i++;
            }
            
            if(ans<distance(p[stack[j]], p[stack[i%size]])){
                ans = distance(p[stack[j]], p[stack[i%size]]);
                ans1 = j;
                ans2 = i%size;
            }
        }
        printf("%lld %lld %lld %lld\n", p[stack[ans1]].x, p[stack[ans1]].y, p[stack[ans2]].x, p[stack[ans2]].y);
        
    }
}