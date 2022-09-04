#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    struct _NODE * next;
    int num;
}NODE;

typedef struct _VERTEX{
    NODE * subnode;
    int parent;
    int subtree;
}VERTEX;

void addEdge(VERTEX * vertex, int from, int to){
    NODE * node = (NODE*)malloc(sizeof(NODE));
    node->num = to;
    node->next = vertex[from].subnode;
    vertex[from].subnode = node;
}

int subnode(VERTEX * vertex, int root){
    int sum =0;
    if(vertex[root].subtree != 0) return vertex[root].subtree;
    NODE *node = vertex[root].subnode;
    while(node!=NULL){
        if(vertex[node->num].parent == root) sum += 1+subnode(vertex, node->num);
        node = node->next;
    }
    vertex[root].subtree = sum;
    return sum;
}

void makeParent(VERTEX * vertex, int root){
    NODE *node = vertex[root].subnode;
    while(node!=NULL){
        if(vertex[node->num].parent == 0){
            vertex[node->num].parent = root;
            makeParent(vertex, node->num);
        }
        node = node->next;
    }
}
int main(void){
    int N, R, Q;
    
    scanf("%d %d %d", &N, &R, &Q);
    VERTEX *vertex = (VERTEX*)malloc(sizeof(VERTEX)*(N+1));
    for(int i=1; i<=N; i++){
        vertex[i].subnode = NULL;
        vertex[i].parent = 0;
        vertex[i].subtree = 0;
    }

    for(int i=0; i<N-1; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        addEdge(vertex, a,b);
        addEdge(vertex, b, a);
    }
    vertex[R].parent = R;
    makeParent(vertex, R);

    for(int i=0; i<Q; i++){
        int query;
        scanf("%d", &query);
        printf("%d\n",subnode(vertex, query)+1);
    }


}