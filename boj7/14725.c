#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TRIE{
    struct _TRIE * next;
    struct _TRIE * child;
    char str[21];
}TRIE;

TRIE * insert(TRIE * root, char *str){
    TRIE * temp = root->child;
    TRIE * pre = NULL;
    while(temp!=NULL){
        if(strcmp(temp->str, str)==0) return temp;
        else if(strcmp(temp->str, str)<0) {
            pre = temp;
            temp = temp->next;
        }
        else if(strcmp(temp->str, str)>0){
            break;
        }
    }
    
    TRIE * new = (TRIE*)malloc(sizeof(TRIE));
    new->child = NULL;
    new->next = temp;
    strcpy(new->str, str);
    if(pre!=NULL) pre->next = new;
    else root->child = new;

    return new;
}

void anthill(TRIE * root, int height){

    TRIE * temp = root->child;

    while(temp!=NULL){
        for(int i=1; i<=height; i++) printf("--");
        printf("%s\n", temp->str);
        anthill(temp, height+1);
        temp = temp->next;
    }


}
int main(void){

    int n;
    scanf("%d", &n);
    TRIE * root = (TRIE*)malloc(sizeof(TRIE));
    root->next = NULL;
    root->child = NULL;
    for(int i=0; i<n; i++){
        int K;
        scanf("%d", &K);
        TRIE * temp = root;
        for(int j=0; j<K; j++){
            char str[21];
            scanf("%s", str);
            temp = insert(temp,str);
        }

    }
    
    anthill(root,0);
}