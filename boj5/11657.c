#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 60000001



typedef struct _NODE{
    int dest;
    int weight;
    struct _NODE * next;
}NODE;

typedef struct _NODELIST{
    int shortest[10001];
    NODE * head;
}NODELIST;

typedef struct _GRAPH{
    NODELIST *list;
    int V;
}GRAPH;

GRAPH * createGraph(int V){
    GRAPH * graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph->V = V;
    graph->list = (NODELIST*)malloc(sizeof(NODELIST)*(V+1));

    for(int i=1; i<=V; i++){
        graph->list[i].head = NULL;
        graph->list[i].shortest = INF;
    }
    return graph;

}

NODE * newNode(int dest){
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->dest = dest;
    new->next = NULL;
    return new;
}

void addEdge(GRAPH * graph, int from , int to, int weight){
    NODE * node = newNode(to);
    node->weight = weight;
    node->next = graph->list[from].head;
    graph->list[from].head = node;
}

void relax(GRAPH *graph, int index){
    
    NODE * temp = graph->list[index].head;
    while(temp!=NULL){
        if(graph->list[index].shortest !=INF &&graph->list[temp->dest].shortest > graph->list[index].shortest + temp->weight) graph->list[temp->dest].shortest=graph->list[index].shortest + temp->weight;
        temp = temp->next;
    }
}

int verifyCycle(GRAPH * graph, int index){
    NODE * temp = graph->list[index].head;
    while(temp!=NULL){
        if( graph->list[index].shortest != INF && graph->list[temp->dest].shortest > graph->list[index].shortest + temp->weight) return 1;
        temp = temp->next;
    }
    return 0;
}
void bellman_ford(GRAPH *graph){
    
    for(int j=1; j<=graph->V-1; j++){
    for(int i=1; i<=graph->V; i++){
       relax(graph, i);
    }
    }

    for(int i=1; i<=graph->V; i++){
        if(verifyCycle(graph, i)==1) {
            printf("-1\n");
            return;
        }
    }
    for(int i=2; i<=graph->V; i++){
        if(graph->list[i].shortest == INF) printf("-1\n");
        else printf("%lld\n", graph->list[i].shortest);
    }
}

int main(void){
    int N,M;
    scanf("%d %d", &N, &M);
    GRAPH * graph = createGraph(N);
    for(int i=0; i<M; i++){
        int a,b,c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(graph,a,b,c);
    }
    graph->list[1].shortest = 0;
    bellman_ford(graph);
}