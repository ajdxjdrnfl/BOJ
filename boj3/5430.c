#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100000
#define FRONT 1
#define BACK 0

int now = 1;
int deque[MAX_SIZE];
int back=-1, front=-1;
int count=0;
int empty(){
    if(count==0) return 1;
    else return 0;
}
int front_pop(){
    if(empty()==1) return -1;
    else{
        count--;
       front = (front-1+MAX_SIZE)%MAX_SIZE;
       return deque[(front+1)%MAX_SIZE];
    } 
    
}
int back_pop(){
    if(empty()==1) return -1;
    else {
        count--;
        back = (back +1 )%MAX_SIZE; 
        return deque[back];   
    }
}
void push_front(int num){
    count++;
    front = (front+1)%MAX_SIZE;
    deque[front] = num;
}
void push_back(int num){
    count++;
    back = (back-1+MAX_SIZE)%MAX_SIZE;
    deque[(back+1)%MAX_SIZE] = num;
}

void R(){
    
    if(now==FRONT) now = BACK;
    else if(now==BACK) now = FRONT;
}

void D(){
    
    if(now==FRONT)back_pop();
    else if(now==BACK) front_pop();
}
int main(void){
    int num;
    scanf("%d", &num);
    for(int i=0; i<num; i++){
        int d_num=0;
        back=-1, front=-1, count=0, now=1;
        char f[100001];
        char a[10100001];
        int n;
        scanf("%s", f);
        scanf("%d", &n);
        scanf("%s", a);
        char *ptr = strtok(a, "[,]");
        while(ptr!=NULL){
            int num = atoi(ptr);
            push_front(num);
            ptr = strtok(NULL, "[,]");
        }
        for(int j=0; f[j]!='\0'; j++){
            if(f[j]=='R') R();
            else if(f[j]=='D') {
                d_num++;
                D();
            }
        }
        
        if(d_num > n) {
            printf("error\n");
            continue;
        }
        printf("[");
        for(int j=0; empty()!=1; j++){
            if(j!=0) printf(",");
        
            if(now==FRONT){
                printf("%d", back_pop());
            }
            else if(now==BACK){
                printf("%d", front_pop());
            }
        }
        printf("]\n");
        }
    }
