#include <stdio.h>
#include <stdlib.h>
#define S 0
#define T 1
#define Y 2
#define X 3
#define Z 4

int * arr;
int LENGTH=0;
typedef struct _VERTEXNODE{
    int num;
    int weight;
    struct _VERTEXNODE * next;
}VERTEXNODE;

typedef struct _VERTEXT{
    int key;
    int pi;
    VERTEXNODE * head;
}VERTEX;

typedef struct _GRAPH{
    int size;
    VERTEX * arr;
}GRAPH;

VERTEXNODE * NewVertexNode(int num){
    VERTEXNODE * newNode = (VERTEXNODE * )malloc(sizeof(VERTEXNODE));
    newNode->num=num;
    newNode->weight=0;
    newNode->next = NULL;
    return newNode;
}
void addEdge(GRAPH * graph, int from, int to, int weight){
    
    VERTEXNODE * newNode = NewVertexNode(to);
    newNode->weight = weight;
    newNode->next = graph->arr[from].head;
    graph->arr[from].head = newNode;
    
}

GRAPH * CreateGraph(int size){
    
    GRAPH * graph = (GRAPH * )malloc(sizeof(GRAPH));
    graph->size = size;
    graph->arr = (VERTEX * )malloc(size*sizeof(VERTEX));
    
    for(int i=0; i<size; i++){
        graph->arr[i].head =NULL;
        graph->arr[i].key = 10000;
        graph->arr[i].pi = -1;
    }

    return graph;
}


void MinHeapify(GRAPH *graph, int index){
    
    int left = index*2;
    int right = index*2+1;
    int smallest = index;
    int temp;
    if(left<=LENGTH && graph->arr[arr[left]].key<graph->arr[arr[smallest]].key) smallest = left;
    if(right<=LENGTH && graph->arr[arr[right]].key<graph->arr[arr[smallest]].key) smallest = right;
    
    if(smallest != index){
        temp = arr[smallest];
        arr[smallest] = arr[index];
        arr[index] = temp;
        MinHeapify(graph, smallest);
    }
    
}

void MakeMin(GRAPH *graph){
    if(arr==NULL){
        
        arr = (int *)malloc((graph->size+1)*sizeof(int));
        LENGTH = graph->size;
        
        for(int i=1; i<=graph->size; i++){
            arr[i] = i-1;
        }
    }
    
    for(int i=LENGTH/2; i>0; i--){
        MinHeapify(graph, i);
    }
    
}

int ExtractMin(GRAPH *graph){
    int result = arr[1];
    
    arr[1] = arr[LENGTH--];
    
    MinHeapify(graph, 1);
    return result;
}
void UpdateMin(GRAPH * graph){
    for(int i=LENGTH/2; i>0;i--){
        MinHeapify(graph, i);
    }
}
void Dijkstras(GRAPH * graph){
    graph->arr[S].key = 0;
   
    MakeMin(graph);
   
    int index=ExtractMin(graph);
   
    
    while(LENGTH>0){
        
        for(VERTEXNODE * node = graph->arr[index].head; node; node = node->next){
            if(graph->arr[node->num].key > graph->arr[index].key + node->weight) graph->arr[node->num].key =  graph->arr[index].key + node->weight;
        }
        
        UpdateMin(graph);
        
        index = ExtractMin(graph);
        
        
    }
    

}

int main(void){
  
    GRAPH * graph = CreateGraph(5);
    addEdge(graph, S,T,10);
    addEdge(graph, S,Y,5);
    addEdge(graph, T,X,1);
    addEdge(graph, T,Y,2);
    addEdge(graph, X,Z,4);
    addEdge(graph, Z,X,6);
    addEdge(graph, Z,S,7);
    addEdge(graph, Y,T,3);
    addEdge(graph, Y,X,9);
    addEdge(graph, Y,Z,2);

    Dijkstras(graph);
   
    for(int i=0; i<graph->size; i++){
         printf("%d : %d \n",i,graph->arr[i].key);
    }
}

