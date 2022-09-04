#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define RED 1
#define BLUE 0

typedef struct _NODE{
    int dest;
    struct _NODE *next;
}NODE;

typedef struct _NODELIST{
    NODE *head;
}NODELIST;
typedef struct _GRAPH{
    int size;
    NODELIST *list;
}GRAPH;

NODE* newNode(int dest){
    NODE * newNode =(NODE*)malloc(sizeof(NODE));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
} 

GRAPH * createGraph(int size){
    GRAPH * graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph->size = size;
    graph->list = (NODELIST*)malloc(sizeof(NODELIST)*size);

    for(int i=0; i<size; i++){
        graph->list[i].head = NULL;
    }
    return graph;
}

void addEdge(GRAPH *graph, int from, int to){
    NODE* check = graph->list[from].head;
    NODE* new = newNode(to);
    
    new->next = graph->list[from].head;
    graph->list[from].head = new;
}

GRAPH* arr;
int color[20001];
int que[200001];
int rear=0, front=0;
int V,E;


void init(int size){
    arr = createGraph(size);
    memset(color, -1, sizeof(color));
}

int bfs(int index){
    
    que[front++] = index;
    
    while(rear<front){
       
        int tempNum = que[rear++];
        NODE* temp = arr->list[tempNum].head;
    
        while(temp!=NULL){
            
            if(color[temp->dest]==-1){
                que[front++] = temp->dest;
                color[temp->dest] = 1-color[tempNum]; 
            }
            else if(color[tempNum]==color[temp->dest]) return 0;
            temp = temp->next;
        }
    }
    return 1;
}

int main(void){
    int test;
    scanf("%d", &test);
    while(test--){
        scanf("%d %d", &V, &E);
        rear=0, front=0;
        init(V+1);
        for(int i=0; i<E; i++){
            int a,b;
            scanf("%d %d", &a, &b);
            addEdge(arr, a,b);
            addEdge(arr, b,a);
            
        }

        for(int i=1; i<=V; i++){
            if(color[i]==-1){
               
                color[i]=BLUE;
                if(bfs(i)!=0);
                else {
                    printf("NO\n");
                    break;
                }
            }
            if(i==V-1) printf("YES\n");
        }

    }
}