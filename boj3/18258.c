#include <stdio.h>
#include <string.h>
int queue[2000001];
int rear=-1;
int fro=-1;

int empty(){
    if(rear == fro) return 1;
    else return 0; 
}

void push(int num){
    queue[++fro]=num;
}

int pop(){
    if(empty()==1) return -1;
    else return queue[++rear];
}

int size(){
    return fro-rear;
}

int front(){
    if(empty()==1) return -1;
    else return queue[rear+1];
}

int back(){
    if(empty()==1) return -1;
    else return queue[fro];
}
int main(void){
    int N;
    scanf("%d", &N);
    
    for(int i=0; i<N; i++){
        char temp[10];
        int num;
        scanf("%s", temp);
        if(strcmp(temp, "push")==0){
            scanf("%d", &num);
            push(num);
        }
        else if(strcmp(temp, "pop")==0){
            printf("%d\n",pop());
        }
        else if(strcmp(temp, "size")==0){
            printf("%d\n",size());
        }
        else if(strcmp(temp, "empty")==0){
            printf("%d\n",empty());
        }
        else if(strcmp(temp, "front")==0){
            printf("%d\n",front());
        }
        else if(strcmp(temp, "back")==0){
            printf("%d\n",back());
        }
    }
}