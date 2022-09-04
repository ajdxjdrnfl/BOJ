#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TRIE{
    struct _TRIE ** next;
    int last;
}TRIE;

TRIE * newTRIE(int last){
    TRIE * new = (TRIE*)malloc(sizeof(TRIE));
    new->next = (TRIE**)malloc(sizeof(TRIE*)*26);
    for(int i=0; i<26; i++){
        new->next[i] = NULL;
    }
    new->last = last;
    return new;
}

void insertTRIE(TRIE * root, char * str){
    TRIE *temp = root;
    int len = strlen(str);
    for(int i=0; i<len; i++){
        if(temp->next[str[i]-'a']!=NULL) temp = temp->next[str[i]-'a'];
        else {
            temp->next[str[i]-'a'] = newTRIE(-1);
            temp = temp->next[str[i]-'a'];
        }
        if(i==len-1) temp->last = 1;
    }
}

int findTRIE(TRIE *root, char *str){
    TRIE *temp = root;
    int len = strlen(str);
    for(int i=0; i<len; i++){
        if(temp->next[str[i]-'a']==NULL) return 0;
        else temp = temp->next[str[i]-'a'];
    }
    if(temp->last == 1) return 1;
    else return 0;
}
int main(void){

    int N,M, result=0;
    scanf("%d %d", &N, &M);
    TRIE * root = newTRIE(-1);

    for(int i=0; i<N; i++){
        char temp[505];
        scanf("%s", temp);
        insertTRIE(root, temp);
    }
    for(int i=0; i<M; i++){
        char temp[505];
        scanf("%s", temp);
        result+=findTRIE(root, temp);
    }
    printf("%d\n", result);
}