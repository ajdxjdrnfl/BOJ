#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _POINT{
    int y1;
    int y2;
}POINT;

typedef struct _VECTOR{
    int *arr;
    int size;
    int last;
}VECTOR;

POINT p[100001];
VECTOR vec[200001];

int max(int a, int b){
    return a>b?a:b;
}

void doubleVec(VECTOR *vec){
    vec->arr = (int*)realloc(vec->arr, sizeof(int)*2*vec->size);
    vec->size *= 2;
}
void push_back(VECTOR *vec, int key){
    if(vec->last>=vec->size-1) doubleVec(vec);
    vec->arr[++vec->last] = key;
}

int com(const void*a, const void*b){
    int pa = *(int*)a;
    int pb = *(int*)b;
    if(pa<pb) return -1;
    else if(pa>pb) return 1;
    else return 0;
}

void lazy_update(int *tree, int *lazy, int node, int start, int end){

    if(lazy[node]){
        tree[node] += lazy[node];
        if(start!=end){
            lazy[node*2] += lazy[node];
            lazy[node*2+1] += lazy[node];
        }
        lazy[node] = 0;
    }

}

void update(int *tree, int *lazy, int node, int start, int end, int left, int right, int value){

        lazy_update(tree, lazy, node, start, end);
        
        if(left>end || right<start) return;
        if(left<=start && end<=right){
            tree[node] += value;
            if(start!=end){
                lazy[node*2] += value;
                lazy[node*2+1] += value;
            }
            return;
        }
        int mid = (start+end)/2;
        update(tree, lazy, node*2 , start, mid, left, right, value);
        update(tree, lazy, node*2+1, mid+1, end, left, right, value);
        tree[node] = max(tree[node*2], tree[node*2+1]);
}  

int query(int *tree, int *lazy, int node, int start, int end, int left, int right){
    lazy_update(tree, lazy, node, start, end);
    if(left>end || right<start) return 0;
    if(left<=start && end <= right ) return tree[node];
    int mid =(start+end)/2;
    return max(query(tree, lazy, node*2, start, mid, left, right), query(tree,lazy,node*2+1,mid+1,end,left,right));
}


void BinarySearch(int *arr, int size, int *object){

    int left=0, right =size-1;
    while(left<=right){
       
        int mid = (left+right)/2;
        int temp = arr[mid];
        if(*object == temp) {
            *object = mid+1;
            return;
        }
        else if(*object < temp) {
            right = mid-1;
        }
        else {
            left = mid+1;
        }
    }

}

void findPosition(int *arr ,int size, POINT *p, int p_size){
    
    for(int i=0; i<p_size; i++){
        BinarySearch(arr, size, &p[i].y1);
        BinarySearch(arr, size, &p[i].y2);
    }
}
int main(void){

    int N;
    scanf("%d", &N);
    int n =1 ;
    while(2*N>=n) n*=2;
    n*=4;

    int tree[n+1];
    int lazy[n+1];
    int num[200001];
    
    memset(tree, 0 ,sizeof(tree));
    memset(lazy, 0 , sizeof(lazy));
    for(int i=0; i<N; i++){
        int a,b,c,d;
        scanf("%d %d %d %d", &a, &b, &c, &d);
        p[i].y1 = d;
        p[i].y2 = b;
        num[i*2+0] = d;
        num[i*2+1] = b;      
    }
    
    int coord[200001];
    int c_size=0;
    int past = -1;
    qsort(num, 2*N, sizeof(int), com);
    for(int i=0; i<2*N; i++){
        if(i==0){
            past = num[i];
            coord[c_size++] = num[i];
        }
        
        else{
            if(past==num[i]) continue;
            else {
                past = num[i];
                coord[c_size++] = num[i];
            }
        }
    }
    findPosition(coord, c_size, p, N);
    memset(vec, 0 ,sizeof(vec));
    int END[200001];
    memset(END, 0 ,sizeof(END));
    
    for(int i=1; i<=c_size; i++){
        vec[i].last = -1;
        vec[i].size = 1;
        vec[i].arr = (int*)malloc(sizeof(int));
    }
    for(int i=0; i<N; i++){
        push_back(&vec[p[i].y1], p[i].y2);
        END[p[i].y2+1]++;
    }
    for(int i=0; i<N; i++){    
        update(tree, lazy, 1, 1, c_size, p[i].y1, p[i].y2, 1);
    }   
    int ans = query(tree, lazy, 1, 1, c_size, 1, c_size);
    int cnt = 0;
    
    for(int i=1; i<=c_size; i++){
        for(int j=0; j<=vec[i].last; j++){
            cnt++;
            update(tree, lazy, 1, 1, c_size , i , vec[i].arr[j],-1);
        }
        cnt -= END[i];
        ans = max(ans, cnt+query(tree, lazy, 1, 1, c_size, 1, c_size));
    }
    printf("%d\n", ans);
}