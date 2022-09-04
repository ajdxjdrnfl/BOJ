#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 200000

int id = 1;
int parent[MAX+1];
int friend[MAX+1];

typedef struct _HASHNODE{
    struct _HASHNODE *next;
    char name[21];
    int id;
}HASHNODE;

typedef struct _HASHMAP{
    HASHNODE *node;
}HASHMAP;

int hashSecret(char *s){
    char temp;
    int result=0;
    temp = s[0];
    for(int i=0; temp; i++){
        result +=temp*(i+1);
        temp = s[i+1];
    }
    return result;
}

HASHNODE* makeNode(char *s){
    HASHNODE *temp = (HASHNODE*)malloc(sizeof(HASHNODE));
    temp->next = NULL;
    strcpy(temp->name, s);
    parent[id] = id;
    friend[id] = 1;
    temp->id = id++;
    return temp;
}
void hashInsert(HASHMAP *map, char *s){
    int hashIndex = hashSecret(s);
    
    HASHNODE * node = map[hashIndex].node;
    while(node!=NULL){
        if(strcmp(node->name, s)==0) return;
        node = node->next;
    }
    node = makeNode(s);
    node->next = map[hashIndex].node;
    map[hashIndex].node = node;
    
}

HASHMAP * makeMap(int V){
    HASHMAP * map = (HASHMAP*)malloc(sizeof(HASHMAP)*(V+1));
    for(int i=1; i<=V; i++){
        map[i].node = NULL;
    }
    return map;
}

int mapValue(HASHMAP * map, char *s){
    int index = hashSecret(s);

    HASHNODE * node = map[index].node;
  
    while(node!=NULL){
       
        if(strcmp(node->name, s)==0) {
        
            return node->id;
        }
        node = node->next;
    } 
}

int checkP(int index){

    while(index!=parent[index]){
        index = parent[index];
    }
    return index;
}

int networkNum(int index){
    int ap = checkP(index);
    return friend[ap];
}
int main(void){
    int T;
    scanf("%d", &T);
    while(T--){
        memset(parent, 0, sizeof(parent));
        memset(friend, 0, sizeof(friend));
        id = 1;
        int F;
        HASHMAP * map = makeMap(MAX);
        scanf("%d", &F);
        for(int i=0; i<F; i++){
            char a[100], b[100];
            scanf("%s %s", a,b);
            hashInsert(map, a);
            hashInsert(map, b);

            int ap = checkP(mapValue(map, a));
            int bp = checkP(mapValue(map, b));
          
            if(ap != bp){
                if(friend[ap] > friend[bp]){
                    parent[bp] = ap;
                    friend[ap]+=friend[bp];
                }
                else{
                    parent[ap] = bp;
                    friend[bp] += friend[ap];
                }
            }
            printf("%d\n", networkNum(ap));
        } 
    }
}