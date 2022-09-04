#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _POINT{
    int x;
    int y;
    long long left;
    long long right;
}POINT; 

POINT p[200001];


int compY(const void*a, const void*b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    if(pa.y < pb.y) return -1;
    else if(pa.y>pb.y) return 1;
    return 0;
}

int compAsc(const void*a, const void *b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    if(pa.x < pb.x) return -1;
    else if(pa.x>pb.x) return 1;
    else{
        if(pa.y<pb.y) return -1;
        else if(pa.y>pb.y) return 1;
        return 0;
    }
}

int compDes(const void*a, const void *b){
    POINT pa = *(POINT*)a;
    POINT pb = *(POINT*)b;
    if(pa.x < pb.x) return 1;
    else if(pa.x>pb.x) return -1;
    else{
        if(pa.y<pb.y) return -1;
        else if(pa.y>pb.y) return 1;
        return 0;
    }
}
long long query(long long*tree, int node, int rear, int front, int start, int end){
    if(rear>front) return 0;
    if(front<start || end < rear) return 0;
    if(rear<=start && end <= front)  return tree[node];

    int mid = (start+end)/2;
    return (query(tree, node*2, rear, front, start, mid) + query(tree, node*2+1, rear, front, mid+1, end))%1000000007;
}
void update(long long *tree, int node, int index, int start, int end){

    if(index<start || index>end) return;

    tree[node]++;
    if(start!=end){
    int mid = (start+end)/2;
    update(tree, node*2, index,start, mid);
    update(tree, node*2+1, index, mid+1, end);
    }   
}
int main(void){

    int N;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d %d", &p[i].x, &p[i].y);
        p[i].left = 0;
        p[i].right = 0;
    }
    
    qsort(p, N, sizeof(POINT), compY);
    
    int cnt=0;
    int last;
    for(int i=0; i<N; i++){
        if(i==0) {
            last = p[i].y;
            p[i].y = cnt++;
        }
        else if(p[i].y!=last){
            last = p[i].y;
            p[i].y = cnt++;
        }
        else p[i].y = (cnt-1);
    }
    long long left_tree[1<<17];
    long long right_tree[1<<17];
    memset(left_tree, 0, sizeof(left_tree));
    memset(right_tree, 0, sizeof(right_tree));

    qsort(p, N, sizeof(POINT), compAsc); 
    for(int i=0; i<N; i++){
        if(i>0 && p[i].y==p[i-1].y && p[i].x==p[i-1].x) {
            p[i].left = p[i-1].left;
            p[i].right = p[i-1].right;
            update(left_tree, 1, p[i].y, 0, cnt-1);
            continue;
        }
        
        p[i].left = query(left_tree, 1, p[i].y+1, cnt-1, 0, cnt-1)%1000000007;;
        update(left_tree, 1, p[i].y, 0, cnt-1);
    }
    qsort(p, N, sizeof(POINT), compDes);
    for(int i=0; i<N; i++){
        if(i>0 && p[i].y==p[i-1].y && p[i].x==p[i-1].x) {
            p[i].left = p[i-1].left;
            p[i].right = p[i-1].right;
            update(right_tree, 1, p[i].y, 0, cnt-1);
            continue;
        }
        p[i].right = query(right_tree, 1, p[i].y+1, cnt-1, 0, cnt-1)%1000000007;
        update(right_tree, 1, p[i].y, 0, cnt-1);
    }
    long long result = 0;
    for(int i=0; i<N; i++){
     
     result = (result + (p[i].left*p[i].right)%1000000007)%1000000007;
    }
    printf("%lld\n", result);


}