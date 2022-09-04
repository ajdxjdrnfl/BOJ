#include <stdio.h>
#include <stdlib.h>

int heap[801];
int heap_size;
int shortest[801];
#define INF 200000001

typedef struct _NODE{
    int dest;
    int weight;
    struct _NODE *next;
}NODE;

typedef struct _NODELIST{
    NODE * head;
}NODELIST;

typedef struct _GRAPH{
    int V;
    NODELIST *list;
}GRAPH;


void swap(int a, int b){
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}
void heapify(int index){

    int min = index;
    if(index*2<=heap_size && shortest[heap[index*2]]<shortest[heap[min]]) min = index*2;
    if(index*2+1<=heap_size && shortest[heap[index*2+1]]<shortest[heap[min]]) min = index*2+1;

    if(min!=index){
        swap(min, index);
        heapify(min);
    }
}
void make_heap(){
    for(int i=1; i<=heap_size; i++){
        heap[i] = i;
    }
 
    for(int i=heap_size/2; i>=1; i--){
        heapify(i);
    }
}

int extract_min(){
    int temp = heap[1];
    heap[1] = heap[heap_size--];
    heapify(1);
    return temp;
}

void relax(GRAPH* graph, int index){

    NODE * temp = graph->list[index].head;
    while(temp!=NULL){
        if(shortest[temp->dest]>shortest[index]+temp->weight) shortest[temp->dest] = shortest[index] + temp->weight;
        temp = temp->next;
    }
}
void updateHeap(){
    for(int i=heap_size/2; i>=1; i--){
        heapify(i);
    }
}
void dijkstra(GRAPH *graph, int start){
    for(int i=1; i<=graph->V; i++){
        if(i!=start) shortest[i] = INF;
        else shortest[i] = 0;
    }
    heap_size = graph->V;
    make_heap();
    while(heap_size>0){
        int min = extract_min();
        relax(graph, min);
        updateHeap();
    }
    
}

NODE* newNode(int dest){
    NODE* new = (NODE*)malloc(sizeof(NODE));
    new->dest = dest;
    new->weight=0;
    new->next = NULL;
    return new;
}
GRAPH * createGraph(int size){

    GRAPH* temp = (GRAPH*)malloc(sizeof(GRAPH));
    temp->V =size;
    temp->list = (NODELIST*)malloc(sizeof(NODELIST)*(size+1));

    for(int i=1; i<=size; i++){
        temp->list[i].head = NULL;
    }
    return temp;
}

void addEdge(GRAPH * graph,int from, int to, int weight){
    NODE * new = newNode(to);
    new->weight=weight;
    new->next = graph->list[from].head;
    graph->list[from].head = new;   
}

int min(int a, int b){
    if(a!=-1 && b!=-1) return a>b?b:a;
    if(a==-1) return b;
    if(b==-1) return a;
    

}
int main(void){

    int V,E;
    scanf("%d %d", &V, &E);
    GRAPH *graph = createGraph(V);
    for(int i=0; i<E; i++){
        int a, b,c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(graph,a,b,c);
        addEdge(graph,b,a,c);
    }
    int a,b;
    scanf("%d %d", &a, &b);
    dijkstra(graph, 1);
    int one_a = shortest[a];
    int one_b = shortest[b];
    dijkstra(graph, a);
    int atob = shortest[b];
    int aton = shortest[graph->V];
    dijkstra(graph,b);
    int bton = shortest[graph->V];

    int left,right;
    if(one_a!=INF && atob!=INF && bton!=INF) left = one_a+atob+bton;
    else left = -1;

    if(one_b!=INF && atob!=INF && aton!=INF) right = one_b+atob+aton;
    else right = -1;

    int result = min(left, right);
    if(result != -1) printf("%d\n", result);
    else printf("-1\n");
}