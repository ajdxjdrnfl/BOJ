#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _EGG{
    int x;
    int y;
}EGG;

typedef struct _PARADE{
    int x1;
    int x2;
    int y;
    int start;
}PARADE;

int compE(const void *a, const void *b){
    EGG pa =*(EGG*)a;
    EGG pb =*(EGG*)b;
    if(pa.y<pb.y) return -1;
    else if(pa.y>pb.y) return 1;
    return 0;
}

int compP(const void*a, const void *b){
    PARADE pa =*(PARADE*)a;
    PARADE pb = *(PARADE*)b;
    if(pa.y<pb.y) return -1;
    else if(pa.y>pb.y) return 1;
    else{
        if(pa.start>pb.start) return -1;
        else if(pa.start<pb.start) return 1;
        else return 0;
    }
}
void propa(int *tree, int *lazy, int node, int start, int end){
    tree[node] += (end-start +1)*lazy[node];
    if(start!=end){
        lazy[node*2] += lazy[node];
        lazy[node*2+1] += lazy[node];
    }
    lazy[node] = 0;
}
void update(int *tree, int *lazy, int node, int rear, int front, int start, int end, int value){
    if(rear>end || front <start) return ;
    if(rear<=start && end <= front) {
        lazy[node] += value;
        return ;
    }
    if(lazy[node]!=0) propa(tree, lazy, node, start, end);
    int mid = (start+end)/2;
    update(tree, lazy, node*2, rear, front, start, mid, value);
    update(tree, lazy, node*2+1, rear, front, mid+1, end, value);
}

int find(int *tree, int *lazy, int node, int index, int start, int end){
    
    if(lazy[node]!=0) propa(tree, lazy, node, start, end);
    if(start==end) return tree[node];
    int mid = (start+end)/2;
    if(mid>=index) return find(tree, lazy, node*2, index, start, mid);
    else return find(tree, lazy, node*2+1, index, mid+1, end); 
}
int main(void){
    int T;
    scanf("%d",&T);
    while(T--){
        int n,m;
        EGG egg[10001];
        PARADE p[100001];
        scanf("%d %d", &n, &m);
        for(int i=0; i<n; i++){
            scanf("%d %d", &egg[i].x, &egg[i].y);
        }
        for(int i=0; i<m; i++){
            scanf("%d %d %d %d", &p[2*i+0].x1, &p[2*i+0].x2, &p[i*2+0].y, &p[i*2+1].y);
            p[i*2+1].x1 = p[i*2+0].x1;
            p[i*2+1].x2 = p[i*2+0].x2;
            p[i*2+0].start = 1;
            p[i*2+1].start = -1;
        }
        qsort(egg, n, sizeof(EGG), compE);
        qsort(p, 2*m, sizeof(PARADE), compP);

        int j=0;
        int tree[1<<19];
        int lazy[1<<19];
        memset(tree, 0, sizeof(tree));
        memset(lazy, 0, sizeof(lazy));
        long long result =0;
        int start=-1, end=-1;
        for(int i=0; i<n; i++){
            while(j<2*m){

                if(p[j].y<egg[i].y){
                    start = -1, end =-1;
                    update(tree, lazy, 1, p[j].x1, p[j].x2, 0, 100000, p[j].start);
                    j++;
                }
                else if(p[j].y==egg[i].y){
                    if(p[j].start==1) {
                        update(tree, lazy, 1, p[j].x1, p[j].x2, 0, 100000, p[j].start);
                        start=-1, end=-1;
                    }

                    else if(p[j].start==-1){
                        if(start==-1) start = j;
                        end = j;
                    }
                    j++;
                }
                else break;
            }
            result += find(tree, lazy, 1, egg[i].x, 0, 100000);
            if(i == n-1) break;
            if(start!=-1 && egg[i].y != egg[i+1].y){
                for(int k=start; k<=end; k++) update(tree, lazy,  1, p[k].x1, p[k].x2, 0, 100000, p[k].start);
                start = -1, end=-1;
            }
            
        }
        printf("%lld\n", result);
    
    }
}

