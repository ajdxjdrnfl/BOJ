#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI  3.1415926535
typedef struct _POINT{
    long long x;
    long long y;
}POINT;
POINT p[1001];

long long ccw(POINT a, POINT b, POINT c){
    return (a.x*b.y+b.x*c.y+c.x*a.y) - (b.x*a.y+c.x*b.y+a.x*c.y);
}

long long dist(POINT a, POINT b){
    return (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y);
}

double m_sqrt(double n)
{
    double s=0;
    double t=0;
 
    s = n / 2;
    for (;s != t;)
    {
        t = s;
        s = ( (n / t) + t) / 2;
    }
    return s;
}
int comp1(const void*a, const void*b){
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

int comp2(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;

    if(ccw(p[0], pa, pb)>0) return -1;
    if(ccw(p[0], pa, pb)<0) return 1;
    else{
        if(dist(p[0], pa) < dist(p[0], pb)) return -1;
        else if(dist(p[0], pa)>dist(p[0], pb)) return 1;
        return 0;     
    }
    
}

double dot(POINT a, POINT b){
    double x = a.x*b.x;
    double y = a.y*b.y;
    return x+y;
}
double getAng(POINT a, POINT b, POINT c){
    POINT pa;
    POINT pb;
    pa.x = a.x-b.x;
    pa.y = a.y-b.y;
    pb.x = c.x-b.x;
    pb.y = c.y-b.y;
    
    return acos(dot(pa, pb)/(m_sqrt(pa.x*pa.x+pa.y*pa.y)*m_sqrt(pb.x*pb.x+pb.y*pb.y)));
}
int stack[1001];
int top=-1;


long long pop(){
    return stack[top--];
}

void push(long long num){
    stack[++top] = num;
}

int main(void){

    int N, L;
    scanf("%d %d", &N, &L);
    for(int i=0; i<N; i++){
        scanf("%lld %lld", &p[i].x, &p[i].y);
    }
    
    qsort(p, N, sizeof(POINT), comp1);
    qsort(&p[1], N-1, sizeof(POINT), comp2);
    int i=2;
    push(0);
    push(1);

    while(i<N){
        
        if(top>=1){
            
            int b = pop();
            int a = pop();
            int c = i;
            
            if(ccw(p[b], p[c], p[a])>0){
                push(a);
                push(b);
                push(c);
                i++;
            }
            else if(ccw(p[b], p[c], p[a])==0){
                push(a);
                push(c);
                i++;
            }
            else{
                push(a);
            }
        }
        else push(i++);
    }
    double ans = 0;
    double ang = 0;
    int size = top+1;
    for(int j=0; j<size; j++){
        ans += m_sqrt(dist(p[stack[j]], p[stack[(j+1)%size]]));
        ang += (PI - getAng(p[stack[j]], p[stack[(j+1)%size]], p[stack[(j+2)%size]]));
    }
   
    printf("%.0lf\n", ans+ang*L);



}