#include <stdio.h>
#include <stdlib.h>

#define EARLY 1
#define LATE 0
typedef struct _NODE{
    struct _NODE * next;
    int num;
}NODE;

typedef struct _VERTEX{
    NODE * subnode;
    int parent;
}VERTEX;

int dp[2][1000001];

void addEdge(VERTEX * vertex, int from, int to){
    NODE* node = (NODE*)malloc(sizeof(NODE));
    node->num = to;
    node->next = vertex[from].subnode;
    vertex[from].subnode = node;
}

void makeTree(VERTEX * vertex, int root){
    NODE * node = vertex[root].subnode;
    while(node!=NULL){
        if(vertex[node->num].parent == 0) {
            vertex[node->num].parent = root;
            makeTree(vertex, node->num);
        }
        node = node->next;
    }
}

int min(int a, int b){
    return a<b?a:b;
}
int sns(VERTEX *vertex, int state, int root){
    
    if(dp[state][root]!=0) return dp[state][root];
    NODE* node = vertex[root].subnode;
    int sum =0;
    if(state==LATE){
        while(node!=NULL){
            if(vertex[node->num].parent == root) sum += sns(vertex, EARLY, node->num);
            node=node->next; 
        }
        dp[state][root] = sum;
    }

    else if(state==EARLY){
        while(node!=NULL){
            if(vertex[node->num].parent == root) sum+=min(sns(vertex, LATE, node->num),sns(vertex, EARLY, node->num));
            node = node->next;
        }
        dp[state][root] = 1 + sum;
    }

    return dp[state][root];
}
int main(void){

    int N;
    scanf("%d", &N);
    VERTEX * vertex = (VERTEX*)malloc(sizeof(VERTEX)*(N+1));
    for(int i=1; i<=N; i++){
        vertex[i].subnode = NULL;
        vertex[i].parent = 0;
    }
    for(int i=0; i<N-1; i++){
        int a,b;
        scanf("%d %d", &a,&b);
        addEdge(vertex, a,b);
        addEdge(vertex, b,a);
    }
    vertex[1].parent = 1;
    makeTree(vertex, 1);

    sns(vertex, LATE, 1);
    sns(vertex, EARLY, 1);
    printf("%d\n", min(dp[0][1], dp[1][1]));
}