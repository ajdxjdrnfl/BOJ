#include <stdio.h>
#include <stdlib.h>

#define INF 100000001

int heap[1001];
int heap_size;

typedef struct _NODE{
    int num;
    int weight;
    struct _NODE* next;
}NODE;

typedef struct _NODELIST{
    int shortest;
    int next;
    NODE *head;
}NODELIST;

typedef struct _GRAPH{
    NODELIST *arr;
    int V;
}GRAPH;

NODE* makeNode(int num, int weight){
    NODE* new = (NODE*)malloc(sizeof(NODE));
    new->next = NULL;
    new->num = num;
    new->weight = weight;
    return new;
}

void addEdge(GRAPH* graph, int from, int to, int weight){
    NODE * temp = makeNode(to, weight);
    temp->next = graph->arr[from].head;
    graph->arr[from].head = temp;
}
GRAPH* createGraph(int V){
    GRAPH * graph = (GRAPH*)malloc(sizeof(GRAPH));
    graph->V = V;
    graph->arr = (NODELIST*)malloc(sizeof(NODELIST)*(V+1));
    for(int i=1; i<=V; i++){
        graph->arr[i].head = NULL; 
        graph->arr[i].shortest = INF;
        graph->arr[i].next = 0;
    }
    return graph;
}



void swap(int a, int b){
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}
void heapify(GRAPH *graph, int index){

    int shortest = index;
    if(index*2<=heap_size && graph->arr[heap[index*2]].shortest<graph->arr[heap[shortest]].shortest) shortest = index*2;
    if(index*2+1<=heap_size && graph->arr[heap[index*2+1]].shortest < graph->arr[heap[shortest]].shortest) shortest = index*2+1;

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
int extract_min(GRAPH* graph){
    int temp = heap[1];
    heap[1] = heap[heap_size--];
    heapify(graph,1);
    return temp;
}

void update(GRAPH *graph, int index){
    int num;
    for(int i=1; i<=heap_size; i++){
        if(heap[i]==index) num = i;
    }
    for(int i=num; i>=1; i=i/2){
        heapify(graph, i);
    }
}
void relax(GRAPH * graph, int n){

    NODE *node = graph->arr[n].head;
   
    while(node!=NULL){
        if(graph->arr[node->num].shortest > graph->arr[n].shortest + node->weight) {
           
            graph->arr[node->num].shortest = graph->arr[n].shortest + node->weight;
            graph->arr[node->num].next = n;
        }
        update(graph, node->num);
        node = node->next;
    }
}
void dijkstra(GRAPH *graph, int start){

    graph->arr[start].shortest = 0;
    makeHeap(graph);
    while(heap_size){
        int temp = extract_min(graph);
        relax(graph, temp);
    }

}

void printDijkstra(GRAPH * graph, int num, int result){
    if(graph->arr[num].next != 0){
        printDijkstra(graph, graph->arr[num].next, result+1);
        printf("%d ", num);
    }
    else{
        printf("%d\n", result);
        printf("%d ", num);
    }
}
int main(void){
    int n,m,start, finish;
    scanf("%d %d", &n, &m);
    GRAPH * graph = createGraph(n);
    for(int i=0; i<m; i++){
        int a,b,c;
        scanf("%d %d %d", &a, &b, &c);
        addEdge(graph, a, b, c);
    }
    scanf("%d %d", &start, &finish);
    dijkstra(graph, start);
    printf("%d\n", graph->arr[finish].shortest);
    printDijkstra(graph, finish, 1);
}