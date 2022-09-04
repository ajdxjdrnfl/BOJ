#include <stdio.h>
#include <stdlib.h>

#define INF 3000001

int heap[20001];
int heap_size;
typedef struct _NODE{
    int dest;
    int weight;
    struct _NODE * next;
}NODE;

typedef struct _NODELIST{
    int shortest;
    NODE *head;
}NODELIST;
typedef struct _GRAPH{
    int V;
    NODELIST * list;
}GRAPH;

NODE* newNode(int dest){
    NODE* new = (NODE*)malloc(sizeof(NODE));
    new->dest = dest;
    new->weight = 0;
    new->next = NULL;
    return new;
}

GRAPH* createGraph(int V){
    GRAPH * graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph->V = V;
    graph->list = (NODELIST*)malloc(sizeof(NODELIST)*(V+1));

    for(int i=1; i<=V; i++){
        graph->list[i].head = NULL;
        graph->list[i].shortest = INF;
    }
    return graph;
}

void addEdge(GRAPH * graph, int from, int to, int weight){
    NODE* new = newNode(to);
    new->weight = weight;
    new->next = graph->list[from].head;
    graph->list[from].head = new; 

}

void swap(int a, int b){
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}


void heapify(GRAPH *graph, int index){

     
    int shortest = index;
    if(index*2<=heap_size && graph->list[heap[index*2]].shortest<graph->list[heap[shortest]].shortest) shortest = index*2;
    if(index*2+1<=heap_size && graph->list[heap[index*2+1]].shortest<graph->list[heap[shortest]].shortest) shortest = index*2+1;

    if(index!=shortest){
        swap(shortest, index);
        heapify(graph, shortest);
    }
    return;
}

void make_heap(GRAPH *graph){
    
    heap_size = graph->V;
    for(int i=1; i<=heap_size; i++){
        heap[i]= i;
    }
    for(int i=heap_size/2; i>=1; i--){
        heapify(graph, i);
    }
}


int extract_min(GRAPH* graph){
    int temp = heap[1];
    heap[1] = heap[heap_size--];
    heapify(graph, 1);
    return temp;
}

void Update(GRAPH* graph){
    for(int i=heap_size/2; i>=1; i--){
        heapify(graph, i);
    }
}
void relax(GRAPH * graph, int index){
    
    NODE * temp = graph->list[index].head;
    while(temp!=NULL){
        if(graph->list[temp->dest].shortest > graph->list[index].shortest+temp->weight) graph->list[temp->dest].shortest = graph->list[index].shortest+temp->weight;
        temp = temp->next;
    }
}
void dijkstra(GRAPH * graph, int start){
    
    graph->list[start].shortest=0;
    make_heap(graph);
    while(heap_size!=0){
        int temp = extract_min(graph);
        relax(graph , temp);
        Update(graph);
    }
    
}

int main(void){
    int V,E;
    scanf("%d %d", &V, &E);
    int start;
    scanf("%d", &start);
    
    GRAPH * graph = createGraph(V);

    for(int i=0; i<E; i++){
        int a,b, weight;
        scanf("%d %d %d", &a, &b, &weight);
        addEdge(graph, a, b, weight);
    }

    dijkstra(graph, start);
    for(int i=1; i<=V; i++){
        if(graph->list[i].shortest!=INF) printf("%d\n", graph->list[i].shortest);
        else printf("INF\n");
    }
}