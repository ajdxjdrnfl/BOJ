#include <stdio.h>
#include <string.h>
#define MAX_SIZE 10000
int deq[MAX_SIZE];
int front=0, back=0;

int empty(){
    if(back==front) return 1;
    else return 0;    
}
void push_front(int num){
    
    deq[front]=num;
    front = ((front+1)+MAX_SIZE)%MAX_SIZE;
}
void push_back(int num){
   
    back = ((back-1)+MAX_SIZE)%MAX_SIZE;
    deq[back]=num;
    
}
int pop_front(){
    if(empty()==1) return -1;
    else {
        
        front = ((front-1)+MAX_SIZE)%MAX_SIZE;
        return deq[front];
    }
}
int pop_back(){
    if(empty()==1) return -1;
    else {
        int temp = deq[back];
        back = (back+1+MAX_SIZE)%MAX_SIZE;
        return temp;
    }
}
int size(){
    if(front-back>=0) return front-back;
    else return MAX_SIZE+(front-back);
}

int print_front(){
    if(empty()==1) return -1;
    return deq[(front-1+MAX_SIZE)%MAX_SIZE];
}

int print_back(){
    if(empty()==1) return -1;
    return deq[back];
}
int main(void){

    int N;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        char temp[20];
        scanf("%s", temp);
        if(strcmp(temp, "push_front")==0){
            int num;
            scanf("%d", &num);
            push_front(num);
        }
        else if(strcmp(temp, "push_back")==0){
            int num;
            scanf("%d", &num);
            push_back(num);
        }
        else if(strcmp(temp, "front")==0){
            printf("%d\n", print_front());
        }
        else if(strcmp(temp, "back")==0){
            printf("%d\n", print_back());
        }
        else if(strcmp(temp, "pop_front")==0){
            printf("%d\n", pop_front());
        }
        else if(strcmp(temp, "pop_back")==0){
            printf("%d\n", pop_back());
        }
        else if(strcmp(temp, "size")==0){
            printf("%d\n", size());
        }
        else if(strcmp(temp, "empty")==0){
            printf("%d\n", empty());
        }
    }
}