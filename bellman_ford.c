#include <stdio.h>
#include <stdlib.h>
#define S 0
#define T 1
#define Y 2
#define X 3
#define Z 4

typedef struct _VERTEXNODE{
    
    int num;
    int weight;
    struct _VERTEXNODE * next;

}VERTEXNODE;

typedef struct _VERTEX{
    int key;
    struct _VERTEXNODE * head;
}VERTEX;

typedef struct _GRAPH{
    int size;
    VERTEX *arr;
}GRAPH;

VERTEXNODE * NewVertexNode(int num){
    VERTEXNODE * newNode = (VERTEXNODE *)malloc(sizeof(VERTEXNODE));
    newNode->num = num;
    newNode->weight = 10000;
    newNode->next = NULL;
    return newNode;
}
void addEdge(GRAPH * graph, int from, int to, int weight){
    VERTEXNODE * newNode = NewVertexNode(to);
    newNode->weight = weight;
    newNode->next = graph->arr[from].head;
    graph->arr[from].head = newNode;
    graph->arr[from].key = 10000;
    
}
GRAPH * CreateGraph(int size){
    GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
    graph->size = size;
    graph->arr = (VERTEX *)malloc(size*sizeof(VERTEX));

    for(int i=0; i<size; i++){
        graph->arr[i].key=0;
        graph->arr[i].head = NULL;
    }
    return graph;
}
void Relax(GRAPH * graph, int u, int v, int weight){
    if(graph->arr[v].key>graph->arr[u].key+weight){
        graph->arr[v].key = graph->arr[u].key+weight;
    } 
}

int BellmanFord(GRAPH * graph){
    graph->arr[S].key =0;
    
    for(int i=1; i<graph->size; i++){
        for(int i=0; i<graph->size; i++){
            for(VERTEXNODE * node = graph->arr[i].head; node; node=node->next){
                Relax(graph, i, node->num, node->weight);
            }
        }
         for(int i=0; i<graph->size; i++){
            printf("%d : %d \n",i,graph->arr[i].key);
        }
    }
    
    
    
    for(int i=0; i<graph->size; i++){
            for(VERTEXNODE * node = graph->arr[i].head; node; node=node->next){
                if(graph->arr[node->num].key>graph->arr[i].key+node->weight){
                    return -1;
                }
            }
    return 1;
}
}


int main(void){

 GRAPH *graph = CreateGraph(5);
 addEdge(graph, S,T,6);
 addEdge(graph, S,Y,7);
 addEdge(graph, T,X,5);
 addEdge(graph, T,Y,8);
 addEdge(graph, T,Z,-4);
 addEdge(graph, X,T,-2);
 addEdge(graph, Z,S,2);
 addEdge(graph, Z,X,7);
 addEdge(graph, Y,X,-3);
 addEdge(graph, Y,Z,9);

    if(BellmanFord(graph)){
        for(int i=0; i<graph->size; i++){
            printf("%d : %d \n",i,graph->arr[i].key);
        }
    }

}  