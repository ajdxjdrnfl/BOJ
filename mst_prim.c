#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7
#define I 8

int *arr;
int LENGTH;
int primResult=0;
typedef struct _VertexNode{
    int num;
    int weight;    
    struct _VertexNode *next; 
}VertexNode;

typedef struct _Vertex{
    int pi;
    int key;
    VertexNode *head;
}Vertex;

typedef struct _Graph{
    int size;
    Vertex *arr;
}Graph;
void updateMin(Graph * graph);
void MinHeap(Graph * graph);
void MinHeapify(Graph * graph, int index);
int ExtractMin(Graph * graph);
void GraphPrint(Graph * graph);
void prim(Graph *graph);
void ArrayPrintf();
Graph *createGraph(int size){
   Graph *graph = (Graph*)malloc(sizeof(Graph));
   graph->size = size;
   graph->arr = (Vertex*)malloc(size*sizeof(Vertex));

   for(int i=0; i<size; i++){
       graph->arr[i].head = NULL;
       graph->arr[i].pi = -1;
       graph->arr[i].key = 10000;
   }
   return graph;
}

VertexNode *newVertexNode(int num){
    VertexNode* newNode = (VertexNode*)malloc(sizeof(VertexNode));
    newNode->num = num;
    newNode->weight = 0;
    newNode->next = NULL;

    return newNode;
}

void addEdge(Graph* graph, int from, int to, int weight){
    VertexNode* newNode = newVertexNode(to);
    newNode->weight = weight;
    newNode->next = graph->arr[from].head;
    graph->arr[from].head = newNode;

    newNode = newVertexNode(from);
    newNode->weight = weight;
    newNode->next = graph->arr[to].head;
    graph->arr[to].head = newNode;

}
int main(void){
    Graph* graph = createGraph(9);
    addEdge(graph, A,B,4);
    addEdge(graph,A,H,8);
    addEdge(graph, B,C,8);
    addEdge(graph,B,H,11);
    addEdge(graph,C,D,7);
    addEdge(graph,C,F,4);
    addEdge(graph,C,I,2);
    addEdge(graph,D,E,9);
    addEdge(graph,D,F,14);
    addEdge(graph,E,F,10);
    addEdge(graph,F,G,2);
    addEdge(graph,G,H,1);
    addEdge(graph,G,I,6);
    addEdge(graph,H,I,7);

    srand(time(NULL));
    prim(graph);
    printf("Result : %d \n", primResult);
    
}

void prim(Graph *graph){
    MinHeap(graph);
    while(LENGTH>0){
        
        int i = ExtractMin(graph);
        printf("i 값은 : %d\n", i);
        if(LENGTH==graph->size-1) ;
        else primResult+=graph->arr[i].key;
        for(VertexNode*node=graph->arr[i].head; node; node = node->next){
            
            if(graph->arr[node->num].key>node->weight){
                graph->arr[node->num].key = node->weight;
                graph->arr[node->num].pi = i;
                
            }
        }
        GraphPrint(graph);
        printf("업데이트 전: ");
        ArrayPrintf();
        updateMin(graph);
        printf("업데이트 후: "); 
        ArrayPrintf();  
        
    }
    
}

void MinHeap(Graph * graph){
    LENGTH = graph->size;
    if(arr==NULL) {
         arr = malloc((LENGTH+1)*sizeof(int));
         for(int i=1; i<=LENGTH; i++){
             arr[i] = i-1;
         }
    }
    
    for(int i=LENGTH/2; i>0; i--){
        MinHeapify(graph, i);
    }
}

void MinHeapify(Graph * graph, int index){
    int left = index*2;
    int right = index*2+1;
    int smallest = index;
    int temp;
    if(left<=LENGTH && graph->arr[arr[left]].key < graph->arr[arr[smallest]].key) smallest = left;
    if(right<=LENGTH && graph->arr[arr[right]].key < graph->arr[arr[smallest]].key) smallest = right;
    
    if(smallest!=index){
        temp = arr[smallest];   
        arr[smallest] = arr[index];
        arr[index] = temp;
        MinHeapify(graph,smallest);
    } 
}

int ExtractMin(Graph * graph){
    int result = arr[1];
    arr[1] = arr[LENGTH--];
    MinHeapify(graph,1);

    return result;
}

void updateMin(Graph * graph){
    for(int i=LENGTH/2; i>0; i--){
        MinHeapify(graph, i);
    }
}

void GraphPrint(Graph * graph){
    for(int i=0; i<graph->size; i++){
        printf("%d : %d , ",i, graph->arr[i].key);
    }
    printf("\n");
}

void ArrayPrintf(){
    for(int i=1; i<=LENGTH; i++){
        printf("%d : %d , ",i, arr[i]);
    }
    printf("\n");
}

