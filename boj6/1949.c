#include <stdio.h>
#include <stdlib.h>

#define GOOD 0
#define BAD 1

typedef struct _NODE{
    struct _NODE * next;
    int num;
}NODE;

typedef struct _VERTEX{
    NODE* subnode;
    int parent;
    int population;
}VERTEX;

void addEdge(VERTEX * vertex, int from, int to){
    NODE * node = (NODE*)malloc(sizeof(NODE));
    node->num = to;
    node->next = vertex[from].subnode;
    vertex[from].subnode = node;
}

int dp[2][10001];

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

int max(int a, int b){
    return a>b?a:b;
}
int woosoo(VERTEX * vertex, int state, int root, int acc){
    
    if(dp[state][root] !=0 ) return dp[state][root];

    NODE* node = vertex[root].subnode;
    int sum=0;
    if(state == GOOD){

        while(node!=NULL){
            if(vertex[node->num].parent == root) {
            sum += woosoo(vertex, BAD, node->num, 0);   
            }
            node= node->next;
        }
        dp[state][root] = vertex[root].population + sum;
    }

    else if(state == BAD){
        
        while(node!=NULL){
            if(vertex[node->num].parent == root){
                sum += max(woosoo(vertex, GOOD, node->num, 0), woosoo(vertex, BAD, node->num, acc+1));
            }
            node = node->next;
        }
        
        dp[state][root] = sum;
    }

    return dp[state][root];
}

int main(void){
    int N;
    scanf("%d", &N);
    VERTEX * vertex = (VERTEX*)malloc(sizeof(VERTEX)*(N+1));
    for(int i=1; i<=N; i++){
        scanf("%d", &vertex[i].population);
        vertex[i].parent = 0;
        vertex[i].subnode = NULL;
    } 
    for(int i=0; i<N-1; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        addEdge(vertex, a, b);
        addEdge(vertex, b, a);
    }

    vertex[1].parent = 1;
    makeTree(vertex, 1);

    printf("%d\n", max(woosoo(vertex, GOOD, 1, 0), woosoo(vertex, BAD, 1, 1)));
}   