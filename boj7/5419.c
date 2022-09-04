#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _POINT{
    long long x;
    long long y;
}POINT;

POINT p[75001];

int comp(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;

    if(pa.x<pb.x) return 1;
    else if(pa.x>pb.x) return -1;
    else{
        if(pa.y<pb.y) return -1;
        else if(pa.y>pb.y) return 1;
        return 0;
    }
}
int comp2(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    if(pa.y<pb.y) return -1;
    else if(pa.y>pb.y) return 1;
    return 0;
}
int query(int *tree, int node, int rear, int front, int start, int end){
    if(front<start || end < rear) return 0;
    if(rear<=start && end <= front)  return tree[node];

    int mid = (start+end)/2;
    return query(tree, node*2, rear, front, start, mid) + query(tree, node*2+1, rear, front, mid+1, end);
}
void update(int *tree, int node, int index, int start, int end){

    if(index<start || index>end) return;

    tree[node]++;
    if(start!=end){
    int mid = (start+end)/2;
    update(tree, node*2, index,start, mid);
    update(tree, node*2+1, index, mid+1, end);
    }
}
int main(void){

    int T;
    scanf("%d", &T);
    while(T--){
        int N;
        scanf("%d", &N);
        for(int i=0; i<N; i++){
            scanf("%lld %lld", &p[i].x, &p[i].y);
        }
        qsort(p, N, sizeof(POINT), comp2);
        int cnt=0;    
        int last;
        for(int i=0; i<N; i++){
            if(i==0) {
                last = p[i].y;
                p[i].y = cnt++;
            }
            else if(p[i].y!=last) {
                last = p[i].y;
                p[i].y = cnt++;
            }
            else p[i].y = (cnt-1);
        }
        qsort(p, N, sizeof(POINT), comp);
        int tree[1<<18];
        long long result=0;
        memset(tree, 0, sizeof(tree));
        for(int i=0; i<N; i++){
            int temp = query(tree, 1, 0, p[i].y , 0, cnt-1);
            update(tree, 1, p[i].y, 0, cnt-1);
            result += temp;
        }
        printf("%lld\n", result);
    }
}