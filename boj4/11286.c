#include <stdio.h>
#include <stdlib.h>


int heap[100001];
int size=0;

void swap(int a, int b){
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}
int heapify(int index){

    if(size<index) return 0;

    int largest;
    largest = index;
    if(size>=index*2){
        if(abs(heap[largest])>abs(heap[index*2])) largest = index*2;
        else if(abs(heap[largest])==abs(heap[index*2]) && heap[largest]>heap[index*2]) largest = index*2;  
    }

    if(size>=index*2+1){
        if(abs(heap[largest])>abs(heap[index*2+1])) largest = index*2+1;
        else if(abs(heap[largest])==abs(heap[index*2+1]) && heap[largest]>heap[index*2+1]) largest = index*2+1;  
    }

    
    if(largest != index){
        swap(largest, index);
        heapify(largest);
        return 1;
    }

    return 0;
}
void addheap(int num){
    heap[++size] = num;
    
    for(int i=size/2; i>0; i/=2){
       heapify(i);
    }
    
}

int delheap(){
    if(size==0) return 0;
    int temp = heap[1];
    heap[1] = heap[size--];
    
    heapify(1);
    return temp;
}
int main(void){

    int N;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        int num;
        scanf("%d", &num);
        if(num==0) printf("%d\n",delheap());
        else addheap(num);
    }
}