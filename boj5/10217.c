#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INF  987654321


int heap[1000001];
int now[1000001];
int weight[1000001];
int heap_size=0;
int MAX;
int current;
int current_w;

typedef struct _NODE{
    int dest;
    int weight;
    int cost;
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
        for(int j=0; j<=10000; j++){
        graph->list[i].shortest[j] = INF;
        }
    }
    return graph;

}

NODE * newNode(int dest){
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->dest = dest;
    new->next = NULL;
    return new;
}

void addEdge(GRAPH * graph, int from , int to, int weight, int cost){
    NODE * node = newNode(to);
    node->weight = weight;
    node->cost = cost;
    node->next = graph->list[from].head;
    graph->list[from].head = node;
}

void swap(int a, int b){
    int temp_heap = heap[a];
    int temp_now = now[a];
    int temp_w = weight[a];
    heap[a] = heap[b];
    now[a] = now[b];
    weight[a] = weight[b];
    heap[b] = temp_heap;
    now[b] = temp_now;
    weight[b] = temp_w;
}
void heapify(GRAPH * graph, int index){

    int shorter = index;
    if(index*2<=heap_size && weight[index*2] < weight[shorter] ) shorter = index*2;
    if(index*2+1<=heap_size && weight[index*2+1] < weight[shorter] ) shorter = index*2+1;

    if(shorter!=index){
        swap(index, shorter);
        heapify(graph, shorter);
    }
}

int extract_min(GRAPH * graph){
    int temp = heap[1];
    current = now[1];
    current_w = weight[1];
    now[1] = now[heap_size];
    weight[1] = weight[heap_size];
    heap[1] = heap[heap_size--];
    heapify(graph, 1);
    return temp;
}

void addheap(GRAPH * graph, int n, int c, int w){
    heap[++heap_size] = n;
    now[heap_size] = c;
    weight[heap_size] = w;

    for(int i=heap_size/2; i>=1; i/=2){
        heapify(graph, i);
    }
}

int min(int a, int b){
    return a>b?b:a;
}
void relax(GRAPH * graph, int index, int N, int M, int W){
    
    if(graph->list[index].shortest[M] < W) return;
    NODE * temp = graph->list[index].head;
    while(temp!=NULL){
        if(temp->cost+M <= MAX && graph->list[temp->dest].shortest[M+temp->cost] > temp->weight + W){
            addheap(graph, temp->dest, M+temp->cost, temp->weight+W);
            for(int j=M+temp->cost; j<=MAX; j++){
            if(graph->list[temp->dest].shortest[j] <= temp->weight + W) break;
            graph->list[temp->dest].shortest[j] = temp->weight + W;
            }
        }        
        temp = temp->next;
    }
    
}

void dijkstra(GRAPH * graph, int N, int M){
    
    MAX = M;

    for(int i=0; i<=M; i++){
        graph->list[1].shortest[i] = 0;
    }
    
    
    heap[1] = 1;
    now[1] = 0;
    weight[1] = 0;

    heap_size = 1;
    
    while(heap_size){
        
        int next = extract_min(graph);
        printf(" next : %d,  current : %d  , weight : %d\n", next, current, current_w);
        if(next == N) break;
        relax(graph, next, N, current, current_w);

    }
    
    
}
int main(void){
    int test;
    scanf("%d", &test);
    while(test--){
        
        int N, M, K;
        scanf("%d %d %d", &N, &M, &K);
        GRAPH * graph = createGraph(N);
     
        for(int i=0; i<K; i++){
            int u,v,c,d;
            scanf("%d %d %d %d", &u,&v,&c,&d);
            addEdge(graph, u, v, d, c);
        }
        int result =INF;
        dijkstra(graph, N, M);
        for(int i=0; i<=M; i++){
            if(result>graph->list[N].shortest[i]) result  = graph->list[N].shortest[i];
        }
        if(result!=INF) printf("%d\n", result);
        else printf("Poor KCM\n");
    }

}