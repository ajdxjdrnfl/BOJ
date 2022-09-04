#include <stdio.h>
#include <stdlib.h>
#define INF 1000001

int heap[10001];
int heap_size=0;

typedef struct _EDGE{
    int v;
    int weight;
    struct _EDGE *next;
}EDGE;

typedef struct _VERTEX{
    EDGE * edge;
    int parent;
    int key;
}VERTEX;

typedef struct _GRAPH{
    VERTEX * vertex;
    int V;
}GRAPH;

GRAPH * createGraph(int V){
    GRAPH * graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph->vertex = (VERTEX*)malloc(sizeof(VERTEX)*(V+1));
    graph->V =V;
    
    for(int i=1; i<=V; i++){
        graph->vertex[i].edge = NULL;
        graph->vertex[i].parent = i;
        graph->vertex[i].key = INF;
    }
    return graph;
}

void addEdge(GRAPH *graph, int from, int to, int weight){
    EDGE * edge = (EDGE*)malloc(sizeof(EDGE));
 
    edge->v = to;
    
    edge->weight = weight;
    
    edge->next = graph->vertex[from].edge;
   
    graph->vertex[from].edge = edge;
   
}

void swap(int a, int b){
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}
void heapify(GRAPH *graph, int index){
    int shortest = index;
    if(index*2<=heap_size && graph->vertex[heap[index*2]].key < graph->vertex[heap[shortest]].key) shortest = index*2;
    if(index*2+1<=heap_size && graph->vertex[heap[index*2+1]].key < graph->vertex[heap[shortest]].key) shortest = index*2+1;

    if(shortest!=index){
        swap(shortest, index);
        heapify(graph, shortest);
    }
}
void makeHeap(GRAPH *graph){
    heap_size = graph->V;
    for(int i=1; i<=heap_size; i++){
        heap[i] = i;
    }
    for(int i=heap_size/2; i>=1; i--){
        heapify(graph, i);
    }
}

int extract_min(GRAPH *graph){
    int temp = heap[1];
    heap[1] = heap[heap_size--];
    heapify(graph,1);
    return temp;
}

void update(GRAPH * graph, int index){
    for(int i=index; i>=1; i/=2){
        heapify(graph, i);
    }
}

void relax(GRAPH *graph, int index){

    EDGE * edge = graph->vertex[index].edge;
    while(edge!=NULL){
        if( edge->weight <graph->vertex[edge->v].key){
            graph->vertex[edge->v].parent = index;
            graph->vertex[edge->v].key = edge->weight;

            for(int i=1; i<=heap_size; i++){
                if(heap[i] == edge->v) update(graph, i);
            }
        }
        edge = edge->next;
    }
}

int prim(GRAPH *graph, int root){
    int result=0;
    graph->vertex[root].key = 0;

    makeHeap(graph);

    while(heap_size){
        int index = extract_min(graph);
        result += graph->vertex[index].key;
        relax(graph, index);
       
    }
    return result;
}

int main(void){
    int V,E;
    scanf("%d %d", &V, &E);
    GRAPH * graph = createGraph(V);
    for(int i=0; i<E; i++){
        int a, b,c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(graph,a,b,c);
        addEdge(graph,b,a,c);       
    }
    printf("%d\n", prim(graph,1));
}