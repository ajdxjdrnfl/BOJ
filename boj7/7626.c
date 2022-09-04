#include <stdio.h>
#include <stdlib.h>
typedef struct _REC{
    int x1;
    int x2;
    int y;
    int start;
}REC;

typedef struct _POINT{
    int x;
    int index;
}POINT;

typedef struct _NODE{
    long long acc;
    long long count;
}NODE;

REC p[400001];
POINT x[400001];
int temp[400001];
int compX(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    if(pa.x < pb.x) return -1;
    else if(pa.x > pb.x) return 1;
    else return 0;
}

int compR(const void*a, const void*b){
    REC pa = *(REC*)a;
    REC pb = *(REC*)b;

    if(pa.y<pb.y) return -1;
    else if(pa.y>pb.y) return 1;
    return 0;
}
int max(int a, int b){
    return a>b?a:b;
}
int update(NODE* tree, int node, int rear, int front, int start, int end, int count){

   if(rear>end || front <start) return tree[node].acc;
   
   if(rear<= start && end <= front){
       tree[node].count += count;
       tree[node].acc = temp[end+1] - temp[start];
       
   }
   
   else{
   int mid = (start+end)/2;
    update(tree, node*2, rear, front, start, mid, count);
    update(tree, node*2+1, rear, front, mid+1, end, count);
   }
    if(tree[node].count>0) return tree[node].acc = temp[end+1]-temp[start];
    else {
        tree[node].acc = tree[node*2].acc+tree[node*2+1].acc;
        return tree[node].acc;
    }
   
}

int main(void){

    int N;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d %d %d %d", &x[i*2+0].x, &x[i*2+1].x, &p[i*2+0].y, &p[i*2+1].y);
        x[i*2+0].index = i*2+0;
        x[i*2+1].index = i*2+1;
        p[i*2+0].start = 1;
        p[i*2+1].start = -1;
    }
    
    qsort(x, 2*N, sizeof(POINT), compX);
    
    int cnt=0;
    int last;
    for(int i=0; i<2*N; i++){
        
        if(i==0){
            last = x[i].x;
            temp[cnt] = x[i].x;
            int a = x[i].index/2;
            int b = x[i].index%2;
            if(b==0){
                p[a*2+0].x1 = cnt;
                p[a*2+1].x1 = cnt;
            }
            else if(b==1) {
                p[a*2+0].x2 = cnt;
                p[a*2+1].x2 = cnt;
            }
            cnt++; 
        }
        else if(x[i].x!=last){
          
            last = x[i].x;
            temp[cnt] = x[i].x;
            int a = x[i].index/2;
            int b = x[i].index%2;
            if(b==0){
                p[a*2+0].x1 = cnt;
                p[a*2+1].x1 = cnt;
            }
            else if(b==1) {
                p[a*2+0].x2 = cnt;
                p[a*2+1].x2 = cnt;
            }
            cnt++; 
        }
        else {
           int a = x[i].index/2;
            int b = x[i].index%2;
            if(b==0){
                p[a*2+0].x1 = cnt-1;
                p[a*2+1].x1 = cnt-1;
            }
            else if(b==1) {
                p[a*2+0].x2 = cnt-1;
                p[a*2+1].x2 = cnt-1;
            }
        }
    }

    qsort(p, 2*N, sizeof(REC), compR);
    NODE tree[400001];
    for(int i=0; i<cnt; i++){
        tree[i].acc = 0;
        tree[i].count = 0;
    }
    long long result = 0;
    int tempy = p[0].y;

    for(int i=0; i<2*N; i++){
        result += (p[i].y-tempy)*tree[1].acc;
       
        update(tree, 1, p[i].x1, p[i].x2-1, 0, cnt-1, p[i].start);
        tempy = p[i].y;
        
    }

    printf("%lld\n", result);
}