#include <stdio.h>
#include <stdlib.h>

typedef struct _POINT{
    long long x;
    long long y;
}POINT;

int stack[100001];
int top=-1;

int pop(){
    if(top!=-1) return stack[top--];
    else return -1;
}
void push(int index){
    stack[++top] = index;
}
int comp1(const void*a,  const void*b){
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
int comp2(const void*a,  const void*b){
    POINT pa = *(POINT*)a; 
    POINT pb = *(POINT*)b;
    if(pa.y*pb.x<pb.y*pa.x) return -1;
    if(pa.y*pb.x>pb.y*pa.x) return 1;
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
    return a.x*b.y+b.x*c.y+c.x*a.y - (b.x*a.y+c.x*b.y+a.x*c.y);
}
int main(void){

    int N;
    POINT p[100001];
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%lld %lld", &p[i].x, &p[i].y);
    }
    qsort(p, N, sizeof(POINT), comp1);
    
    for(int i=1; i<N; i++){
        p[i].x = p[i].x - p[0].x;
        p[i].y = p[i].y - p[0].y;
    }
    p[0].x = 0;
    p[0].y = 0;

    qsort(&p[1], N-1, sizeof(POINT), comp2);
    
    push(0);
    push(1);
    int i=2;
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
   
    
    printf("%d\n", top+1);
}