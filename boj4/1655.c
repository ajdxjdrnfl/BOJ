#include <stdio.h>

int min_heap[100001];
int max_heap[100001];
int min_size=0;
int max_size=0;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}
void min_heapify(int index){

    if(index>min_size) return;
    int min = index;
    if(index*2<=min_size && min_heap[min] > min_heap[index*2]) min = index*2;
    if(index*2+1<=min_size && min_heap[min] > min_heap[index*2+1]) min=index*2+1;

    if(min!=index){
        swap(&min_heap[min], &min_heap[index]);
        min_heapify(min);
    }
}

void max_heapify(int index){

    if(index>max_size) return; 
    int max = index;
    if(index*2<=max_size && max_heap[max] < max_heap[index*2]) max = index*2;
    if(index*2+1<=max_size && max_heap[max] < max_heap[index*2+1]) max = index*2+1;

    if(max!=index){
        swap(&max_heap[max], &max_heap[index]);
        max_heapify(max);
    } 
}

void add_minheap(int num){
    min_heap[++min_size] = num;
    for(int i=min_size/2; i>=1; i/=2){
        min_heapify(i);
    }
}

void add_maxheap(int num){
    max_heap[++max_size] = num;
    for(int i=max_size/2; i>=1; i/=2){
        max_heapify(i);
    }
}

int del_minheap(){
    if(min_size!=0){
        int num = min_heap[1];
        min_heap[1] = min_heap[min_size--];
        min_heapify(1);
        return num;
    }
}
int del_maxheap(){
    if(max_size!=0){
        int num = max_heap[1];
        max_heap[1] = max_heap[max_size--];
        max_heapify(1);
        return num;
    }
}
int main(void){

    int N;
    scanf("%d", &N);
    int num;
    for(int i=1; i<=N; i++){
        scanf("%d", &num);
        if(i==1) add_maxheap(num);
        else if(i==2){
            if(max_heap[1]<=num) add_minheap(num);
            else{
                int temp = del_maxheap();
                    add_maxheap(num);
                    add_minheap(temp);
            }
        }
        else if(i%2==1){
            if(max_heap[1]>=num) add_maxheap(num);
            else{
                if(min_heap[1]<num){
                    int temp = del_minheap();
                    add_minheap(num);
                    add_maxheap(temp);
                }
                else add_maxheap(num);
            } 
        }

        else{
            if(min_heap[1]<=num) add_minheap(num);
            else{
                if(max_heap[1]>num){
                    int temp = del_maxheap();
                    add_maxheap(num);
                    add_minheap(temp);
                }
                else add_minheap(num);
            }
        }

        printf("%d\n", max_heap[1]);
    }
}