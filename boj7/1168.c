#include <stdio.h>
#include <string.h>

int tree[800001];

int josep(int node, int index, int start, int end){
    
    if(start==end) return start;
    int mid = (start+end)/2;
    if(index <= tree[node*2]) return josep(node*2, index, start, mid);
    else return josep(node*2+1, index-tree[node*2], mid+1, end);
}
int init(int node, int start, int end){
    if(start==end){
        tree[node]++;
        return tree[node];
    }
    int mid = (start+end)/2;
    int left = init(node*2, start, mid);
    int right = init(node*2+1, mid+1, end);
    tree[node] = left + right;
    return tree[node];
}
void update(int node, int index, int start, int end){

    if(index>end || index<start) return;

    tree[node]--;
    if(start!=end){
    int mid = (start+end)/2;
    if(mid>=index) update(node*2, index, start, mid);
    else update(node*2+1, index, mid+1, end);
    }
}
int main(void){
    int N,K;
    scanf("%d %d", &N, &K);
    memset(tree, 0, sizeof(tree));
    init(1, 1, N);

    printf("<");
    int index = 1;
    for(int i=0; i<N; i++){
        int size = N-i;
        index += (K-1);
        if(index%size==0) index = size;
        if(index>size) index %= size;

        int temp  = josep(1, index, 1, N);

        update(1, temp, 1, N);
        if(i==N-1) printf("%d", temp);
        else printf("%d, ",temp);

    }
    printf(">");
    
}