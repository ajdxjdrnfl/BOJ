#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct _NODE{
    struct _NODE * next;
    int num;
}NODE;

NODE *child[100001];
int in[100001];
int out[100001];
int idx=1;

NODE * getNode(int num){
    NODE* new = (NODE*)malloc(sizeof(NODE));
    new->next = NULL;
    new->num = num;
    return new;
}

void addNode(int from, int to){
    NODE *temp = getNode(to);
    temp->next = child[from];
    child[from] = temp;
}
void euler_tour(int index){
    in[index] = idx++;
    NODE * temp = child[index];
    
    while(temp){
        euler_tour(temp->num);
        temp = temp->next;
    }
    out[index] = idx-1;

}

void lazy_update(int *tree, int *lazy, int node, int start, int end){
    if(lazy[node]){
        if(lazy[node]>0) tree[node] = (end-start+1);
        else tree[node] = 0;
        if(start!=end){
            if(lazy[node]>0){
            lazy[node*2]=1;
            lazy[node*2+1]=1;
            }
            else{
                lazy[node*2] = -1;
                lazy[node*2+1] = -1;
            }
        }
        lazy[node] = 0;

    }
}

void update(int *tree, int *lazy, int node, int start, int end, int left, int right, int value){
    lazy_update(tree, lazy, node, start, end);
    if(left>end || right<start) return;
    if(left<=start && end<= right){
        if(value>0) tree[node] = (end-start+1);
        else tree[node] = 0;
        if(start!=end){
            lazy[node*2] = value;
            lazy[node*2+1] = value;
        }
        return;
    }
    int mid =(start+end)/2;
    update(tree, lazy, node*2, start, mid, left, right, value);
    update(tree, lazy, node*2+1, mid+1, end, left, right, value);
    tree[node] = tree[node*2]+tree[node*2+1];
    return;
}

int query(int *tree, int *lazy, int node, int start, int end, int left, int right){
    lazy_update(tree, lazy, node, start, end);
    if(left>end || right<start) return 0;
    if(left<=start && end<=right) return tree[node];
    int mid =(start+end)/2;
    return query(tree, lazy, node*2, start, mid, left, right) + query(tree, lazy, node*2+1, mid+1, end, left, right);
}
int main(void){

    int N, M;
    scanf("%d", &N);
    for(int i=1; i<N; i++){
        child[i] = NULL;
    }
    for(int i=1; i<=N; i++){
        int temp;
        scanf("%d", &temp);
        if(temp!=0) addNode(temp, i);
    }
    memset(in, 0 , sizeof(in));
    memset(out, 0, sizeof(out));
    euler_tour(1);
    scanf("%d", &M);
    int n = 1;
    while(N>=n) n *= 2;
    n *= 4;

    int tree[n+1];
    int lazy[n+1];
    memset(tree, 0 ,sizeof(tree));
    memset(lazy, 0 ,sizeof(lazy));
    
    update(tree, lazy, 1, 1, N, 1, N, 1);
    for(int i=0; i<M; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        if(a==1){
            if(in[b]!=out[b]) update(tree, lazy, 1, 1, N, in[b]+1, out[b], 1);
        }
        else if(a==2){
            if(in[b]!=out[b]) update(tree, lazy, 1, 1, N, in[b]+1, out[b], -1);
        }
        else if(a==3){
            if(in[b]!=out[b]) printf("%d\n", query(tree, lazy, 1, 1, N, in[b]+1, out[b]));
            else printf("0\n");
        }
    }
}