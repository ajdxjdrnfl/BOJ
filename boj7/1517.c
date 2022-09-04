#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct _NODE{
    int value;
    int index;
}NODE;

int comp(const void*a, const void* b){
    NODE pa = *(NODE*)a;
    NODE pb = *(NODE*)b;
    if(pa.value < pb.value) return -1;
    if(pa.value > pb.value) return 1;
    return 0;
}

long long tree[2000001];

long long bubble(int node, int rear, int front, int start, int end){

    if(rear>front) return 0;

    if(rear>end || front < start) return 0;
    if(rear <= start && front>=end) return tree[node];

    int mid=(start+end)/2;
    return bubble(2*node, rear, front, start, mid) + bubble(2*node+1, rear, front, mid+1, end);
}

void update(int node, int index, int start, int end){
    
    if(index < start || end < index) return;
    tree[node]++;
    if(start!=end){
    int mid = (start+end)/2;
    update(node*2, index, start, mid);
    update(node*2+1, index, mid+1, end);
    }
}
int main(void){
    int N;
    long long ans=0;
    scanf("%d", &N);
    NODE * node = (NODE*)malloc(sizeof(NODE)*(N));
    
    for(int i=0; i<N; i++){
        node[i].index = i;
        scanf("%d", &node[i].value);
    }
    qsort(node, N, sizeof(NODE), comp);
    memset(tree, 0, sizeof(tree));
    for(int i=0; i<N; i++){
       ans += bubble(1, node[i].index+1, N-1, 0, N-1);
       update(1, node[i].index, 0, N-1);
    }
    
    printf("%lld\n", ans);
}