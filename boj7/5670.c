#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TRIE{
    struct _TRIE ** next;
    int size;
    int last;
}TRIE;

TRIE * newTRIE(int last){
    TRIE * new = (TRIE*)malloc(sizeof(TRIE));
    new->next = (TRIE**)malloc(sizeof(TRIE*)*26);
    for(int i=0; i<26; i++){
        new->next[i] = NULL;
    }
    new->size = 0;
    new->last = last;
    return new;
}

void insertTRIE(TRIE * root, char * str){
    TRIE *temp = root;
    int len = strlen(str);
    for(int i=0; i<len; i++){
        if(temp->next[str[i]-'a']!=NULL) temp = temp->next[str[i]-'a'];
        else {
            temp->size++;
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

float Keyboard(TRIE * root,char str[][81], int N){
    int result = 0;
    for(int i=0; i<N; i++){
        TRIE * temp = root;
        int len = strlen(str[i]);
        for(int j=0; j<len; j++){
            char index = str[i][j]-'a';
            if(temp->size!=1) result++;
            else if(temp->last==1) result++;
            temp = temp->next[index];
            
        }
    }
    return ((float)result)/((float)N);
}

void freeman(TRIE * root){
    for(int i=0; i<26; i++){
        if(root->next[i]!=NULL) freeman(root->next[i]);
    }
    free(root->next);
}
int main(void){

    
    int N;
    while(scanf("%d", &N)!=EOF){
    TRIE *root = newTRIE(1);
    char str[N][81];
    for(int i=0; i<N; i++){
        
        scanf("%s", str[i]);
        insertTRIE(root, str[i]);

    }
    float temp = Keyboard(root, str, N);
    printf("%.2f\n", temp);
    freeman(root);
    
    }

}