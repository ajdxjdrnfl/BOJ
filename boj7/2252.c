#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    struct _NODE * next;
    int num;
}NODE;

typedef struct _NODELIST{
    NODE * head;
    int degree;
}NODELIST;

void addEdge(NODELIST * list, int from, int to){
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->num = to;
    new->next = list[from].head;
    list[from].head = new;
    list[to].degree++;
}
int main(void){

    int N,M;
    scanf("%d %d", &N, &M);
    NODELIST * list = (NODELIST*)malloc(sizeof(NODELIST)*(N+1));
    for(int i=1; i<=N; i++){
        list[i].head = NULL;
        list[i].degree = 0;
    }
    for(int i=0; i<M; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        addEdge(list, b, a);
    }
    int que[32001];
    int rear=0, front=0;
    for(int i=1; i<=N; i++){
        if(list[i].degree==0) que[front++] = i;
    }
    while(rear<front){
        
        int index = que[rear++];
        NODE * temp = list[index].head;
        
        while(temp!=NULL){
            list[temp->num].degree--;
            if(list[temp->num].degree == 0) que[front++] = temp->num;
            temp = temp->next;
        }
    }
    for(int i=front-1; i>=0; i--){
        printf("%d ", que[i]);
    }
    printf("\n");

}
