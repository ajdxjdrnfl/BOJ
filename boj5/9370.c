#include <stdio.h>
#include <stdlib.h>
#define INF 2000001
#define TRUE 1
#define FALSE 0

int heap[2001];
int heap_size;
int g,h;
typedef struct _NODE{
    int dest;
    int weight;
    struct _NODE * next;
}NODE;

typedef struct _NODELIST{
    int shortest;
    int able;
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
        graph->list[i].able = FALSE;
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

int com(const void *a, const void *b){
    int pa = *(int*)a;
    int pb = *(int*)b;
    if(pa<pb) return -1;
    else if(pa>pb) return 1;
    return 0;
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

void make_heap(GRAPH *graph, int start){
    
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
    heap[heap_size+1] = temp;
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
        if(graph->list[temp->dest].shortest > graph->list[index].shortest+temp->weight){
            graph->list[temp->dest].shortest = graph->list[index].shortest+temp->weight;
            if((temp->dest == g && index==h)||(temp->dest==h && index==g)) graph->list[temp->dest].able = TRUE;
            else graph->list[temp->dest].able = graph->list[index].able;
        }
        else if(graph->list[temp->dest].shortest == graph->list[index].shortest+temp->weight){
            if((temp->dest == g && index==h)||(temp->dest==h && index==g)) graph->list[temp->dest].able = TRUE;
            else if(graph->list[index].able) graph->list[temp->dest].able = graph->list[index].able;
        }
        temp = temp->next;
    }
}
void dijkstra(GRAPH * graph, int start){
    
    graph->list[start].shortest=0;

    make_heap(graph, start);
    while(heap_size!=0){
        int temp = extract_min(graph);
        relax(graph , temp);
        Update(graph);
    }
    
}



int main(void){
    int test;
    scanf("%d", &test);
    while(test--){
        int n,m,t;
        scanf("%d %d %d", &n, &m, &t);
        GRAPH * graph = createGraph(n);
        int s;
        scanf("%d %d %d", &s, &g, &h);
        for(int i=0; i<m; i++){
            int a,b,c;
            scanf("%d %d %d", &a, &b, &c);
            addEdge(graph,a,b,c);
            addEdge(graph,b,a,c);
        }
        dijkstra(graph, s);
        int obj[t];
        int obj_size=0;
        for(int i=0; i<t; i++){
            int temp;
            scanf("%d", &temp);
            if(graph->list[temp].able){
                obj[obj_size++] = temp;
            }
        }
        qsort(obj, obj_size, sizeof(int), com);
        for(int i=0; i<obj_size; i++){
            printf("%d ", obj[i]);
        }
        printf("\n");
    }   
}