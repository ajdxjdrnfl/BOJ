#include <stdio.h>
#include <stdlib.h>
int que[1000000];

int back=-1, front=-1;
int empty(){
    if(back==front) return 1;
    else return 0;
}

void push(int num){
    que[(++front)] = num;
}

int pop(){
    if(empty()==1) return -1;
    else return que[(++back)];
}
int main(void){
    int N, K;
    
    scanf("%d %d", &N, &K );

    for(int i=1; i<=N; i++){
        push(i);
    }
    printf("<");
    while(empty()!=1){
        for(int i=1; i<K; i++){
            int temp = pop();
            push(temp);
        }
        printf("%d", pop());
        if(empty()!=1) printf(", ");
    }
    printf(">");
    

    
}