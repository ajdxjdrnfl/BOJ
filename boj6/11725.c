#include <stdio.h>
#include <stdlib.h>

typedef struct _NODE{
    int num;
    struct _NODE * next;
}NODE;

typedef struct _NODELIST{
    NODE * head;
}NODELIST;

void addEdge(NODELIST *list, int from, int to){
    NODE* new = malloc(sizeof(NODE));
    new->num = to;
    new->next = list[from].head;
    list[from].head = new;
}
int que[100001];
int result[100001];
int rear=-1, front=-1;
int main(void){
    int N;
    scanf("%d", &N);
    NODELIST list[100001];
    for(int i=1; i<=N; i++){
        list[i].head =NULL;
    }
    for(int i=0; i<N-1; i++){
        int a, b;
        scanf("%d %d", &a, &b);
        addEdge(list, a, b);
        addEdge(list, b, a);
    }
    int size = 1;
    que[++front] = 1;
    result[1] = 1;
    while(rear<front  && size != N){
        int temp = que[++rear];
        NODE* node = list[temp].head;
        while(node!=NULL){
            if(result[node->num]==0){
                que[++front] = node->num;
                result[node->num] = temp;
                size++;
            }
            node = node->next;
        }
    }
    for(int i=2; i<=N; i++){
        printf("%d\n", result[i]);
    }
    
}