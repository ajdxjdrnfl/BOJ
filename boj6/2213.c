#include <stdio.h>
#include <stdlib.h>

#define IN 0
#define OUT 1

int dp[2][10001];
int re[2][10001];
int stack[10001];
int top=0;

typedef struct _NODE{
    struct _NODE *next;
    int num;
}NODE;

typedef struct _VERTEX{
    NODE *subnode;
    int parent;
    int weight;
}VERTEX;

int comp(const void*a , const void *b){
    int pa = *(int*)a;
    int pb = *(int*)b;
    if(pa<pb) return -1;
    else if(pa>pb) return 1;
    return 0;
}
void addEdge(VERTEX* vertex, int from, int to){
    NODE * node = (NODE*)malloc(sizeof(NODE));
    node->next = vertex[from].subnode;
    node->num = to;
    vertex[from].subnode = node;
}

void makeParent(VERTEX* vertex, int root){
    NODE * node = vertex[root].subnode;
    while(node!=NULL){
        if(vertex[node->num].parent == 0){
            vertex[node->num].parent = root;
            makeParent(vertex, node->num);
        }
        node = node->next;
    }
}

int max(int a, int b){
    return a>b?a:b;
}
int IndeSet(VERTEX * vertex, int state, int root){

    if(dp[state][root]!=0) return dp[state][root];
    
    NODE * node = vertex[root].subnode;
    int sum=0;
    if(state==IN){
        while(node!=NULL){
        if(vertex[node->num].parent == root) sum +=  IndeSet(vertex, OUT, node->num);
        node = node->next;
        }
        dp[state][root] = sum + vertex[root].weight;
        
    }
    else if(state==OUT){
        while(node!=NULL){
            if(vertex[node->num].parent==root) {
                sum += max(IndeSet(vertex, IN, node->num), IndeSet(vertex, OUT, node->num));
            }
            node = node->next;
        }
        
        dp[state][root] = sum;
        
    }
    
    return dp[state][root];
}

void printStack(VERTEX * vertex, int state ,int index){
    
    NODE * node = vertex[index].subnode;
    if(state==IN){
        stack[top++] = index;
        while(node!=NULL){
        if(vertex[node->num].parent == index) printStack(vertex, OUT ,node->num);
        node = node->next;
        }
    }
    else if(state==OUT){
        while(node!=NULL){
            if(vertex[node->num].parent==index) {
                if(dp[IN][node->num]>dp[OUT][node->num]) printStack(vertex, IN, node->num);
                else printStack(vertex, OUT, node->num);
            }
            node = node->next;
        }
        
    }
}
int main(void){
    int N;
    scanf("%d", &N);
    VERTEX * vertex = (VERTEX*)malloc(sizeof(VERTEX)*(N+1));
    for(int i=1; i<=N; i++){
        scanf("%d", &vertex[i].weight);
        vertex[i].subnode = NULL;
        vertex[i].parent = 0;
    }        
    
    for(int i=0; i<N-1; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        addEdge(vertex, a,b);
        addEdge(vertex, b,a);
    }
    vertex[1].parent = 1;
    makeParent(vertex, 1);
    printf("%d\n", max(IndeSet(vertex, IN, 1), IndeSet(vertex, OUT, 1)));
    int state;
    if(dp[OUT][1] < dp[IN][1]) state = IN;
    else state = OUT; 
    printStack(vertex, state, 1);
    qsort(stack, top, sizeof(int), comp);
    for(int i=0; i<top; i++){
        printf("%d ", stack[i]);
    }
    printf("\n");
    
    
}