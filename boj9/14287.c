#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _NODE{
    int num;
    struct _NODE *next;
}NODE;

NODE *child[100001];

int idx = 1;
int dfs_in[100001];
int dfs_out[100001];

void eulerTour(int node){
    dfs_in[node] = idx++;

    NODE* temp = child[node];
    while(temp){
        eulerTour(temp->num);
        temp = temp->next;
    }
    dfs_out[node] = idx-1;
   
    return;
}

NODE *getNode(int num){
    NODE* new = (NODE*)malloc(sizeof(NODE));
    new->next = NULL;
    new->num = num;
    return new;
}

void addNode(int from, int to){
    NODE * new = getNode(to);
    new->next = child[from];
    child[from] = new;
}

int propaganda(int *tree, int *prop, int node, int start, int end){
    if(prop[node]){
        tree[node] += (end-start+1)*(prop[node]);
    
    if(start!=end){
        prop[node*2] += prop[node];
        prop[node*2+1] += prop[node];
    }
    
    prop[node] = 0;
    }
}

void update(int *tree, int* prop, int node, int start, int end ,int left, int right, int value){

    propaganda(tree, prop, node, start ,end);
    if(left>end || right <start) return;
    if(left<=start&& end<=right) {
        tree[node] += (end-start+1)*value;
        if(start!=end){
            prop[node*2] += value;
            prop[node*2+1] += value;
        }
        return ;
    }
    if(start==end) return;
    int mid = (start+end)/2;
    update(tree, prop, node*2, start, mid, left, right, value);
    update(tree, prop, node*2+1, mid+1, end, left, right, value);
    tree[node] = tree[node*2]+tree[node*2+1];
    return;
}

int query(int *tree, int*prop,  int node, int start, int end, int left, int right){

    propaganda(tree, prop, node, start, end );
    if(left>end || right<start) return 0;
    if(left<=start && end <= right){
        return tree[node];
    }
   
    int mid = (start+end)/2;
    return query(tree, prop, node*2, start ,mid, left, right)+query(tree, prop, node*2+1, mid+1, end, left, right);
}

int main(void){

    int n,m;
    scanf("%d %d", &n ,&m);
    
    for(int i=1; i<=n; i++){
        int temp;
        scanf("%d", &temp);
        if(temp!=-1) addNode(temp, i);
    }

    int two = 1;
    while(n>=two) two*=2;
    two*=4;
    int tree[two+1];
    int prop[two+1];
    memset(tree, 0 , sizeof(tree));
    memset(prop, 0 , sizeof(prop));
    eulerTour(1);
    
    for(int i=0; i<m; i++){
        int num;
        scanf("%d", &num);
        if(num==1){
            int a,b;
            scanf("%d %d", &a, &b);
            update(tree, prop,  1, 1, n, dfs_in[a], dfs_in[a], b);
        }
        else if(num==2){
            int a;
            scanf("%d", &a);
            printf("%d\n", query(tree, prop, 1, 1, n, dfs_in[a], dfs_out[a]));
        }
    }
}