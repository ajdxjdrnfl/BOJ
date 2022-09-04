#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _HASHNODE{
    struct _HASHNODE *next;
    char name[25];
    int value;
}HASHNODE;

typedef struct _HASHTABLE{
    HASHNODE *head;
}HASHTABLE;

HASHTABLE *table;
int size;
char strArr[100001][30];
HASHTABLE * makeTable(int V){
    HASHTABLE * temp  = (HASHTABLE*)malloc(sizeof(HASHTABLE)*(V+1));
    for(int i=0; i<V; i++){
        temp[i].head = NULL;
    }
    return temp;
}

HASHNODE *makeNode(char *str, int value){
    HASHNODE * temp = (HASHNODE*)malloc(sizeof(HASHNODE));
    temp->next = NULL;
    strcpy(temp->name, str);
    temp->value = value;
    return temp;
}

int makeSecret(char *str){

    char temp;
    temp = str[0];
    int sum=0;
    for(int i=0; temp; i++){
        sum += temp;
        temp = str[i+1];
    }
    return sum%size;
}

void Insert(char *str, int value){
    int index = makeSecret(str);
    HASHNODE *temp = makeNode(str, value);
    temp->next = table[index].head;
    table[index].head = temp;
}

int find(char *str){
    int index = makeSecret(str);
    HASHNODE *current = table[index].head;
    while(current){
        if(strcmp(current->name, str)==0) break;
        current = current->next;
    }
    return current->value;
}

int main(void){
    int N,M;
    scanf("%d %d", &N, &M);
    size = 100;
    table = makeTable(size);
    
    for(int i=1; i<=N; i++){
        scanf("%s", strArr[i]);  
        Insert(strArr[i], i);      
    }
    for(int i=0; i<M; i++){
        char temp[30];
        scanf("%s", temp);
        if(temp[0]>='0' && temp[0]<='9') {
            int num = atoi(temp);
            printf("%s\n", strArr[num]);
        }
        else printf("%d\n", find(temp));
    }

}