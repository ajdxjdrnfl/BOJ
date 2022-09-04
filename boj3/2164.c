#include <stdio.h>
#define size_num 500000
int que[size_num];
int back=-1;
int front=-1;

int empty(){
    if(back==front) return 1;
    else return 0;
}

void push(int num){
    que[(++front)%size_num]=num;
}

int pop(){
    if(empty()==1) return -1;
    return que[(++back)%size_num];
}
int size(){
    return front-back;
}
int main(void){
    int N;
    scanf("%d", &N);
    for(int i=1; i<=N;i++){
        push(i);
    }
    while(size()>1){
        pop();
        push(pop());
    }
    printf("%d", pop());
}