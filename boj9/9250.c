#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _TRIE{
    struct _TRIE *go[26];
    struct _TRIE *fail;
    int end;
}TRIE;

TRIE *root;

TRIE * makeTRIE(){
    TRIE *new = (TRIE*)malloc(sizeof(TRIE));
    
    for(int i=0; i<26; i++) new->go[i] = NULL;
    new->fail = NULL;
    new->end = 0;
    return new;
}

void makeROOT(){
    root = (TRIE*)malloc(sizeof(TRIE));
    root->fail = root;
    
}

void insert(TRIE *trie, char *str){

    int n = strlen(str);
    TRIE * next = trie;
    for(int i=0; i<n; i++){
        if(!next->go[str[i]-'a']) next->go[str[i]-'a']= makeTRIE();
        next = next->go[str[i]-'a'];
    }
    next->end = 1;    
}

void yaho(TRIE * root, char* str, int n){

    TRIE *temp = root;
    for(int i=0; i<n; i++){
        int next = str[i]-'a';
        while(temp != root && !temp->go[next]){
            temp = temp->fail;
        }
        if(temp->go[next]){
            temp = temp->go[next];
        }
        if(temp->end) {
            printf("YES\n");
            return;
        }
    }
    printf("NO\n");
    return;
}
int main(void){
    int N;
    scanf("%d", &N);
    makeROOT();

    for(int i=0; i<N; i++){
        char temp[110];
        scanf("%s", temp);
        insert(root, temp);
    }
    
    TRIE *que[100001];
    int rear=0, front=0;
    que[front++] = root;
    while(rear<front){

        TRIE * temp = que[rear++];
        for(int i=0; i<26; i++){
            if(temp->go[i]) {
                TRIE * next = temp->go[i];
                que[front++] = next;
                if(temp==root) next->fail = root;
                else{
                TRIE * dest = temp->fail;
                while(dest != root && !dest->go[i]) dest = dest->fail;
                if(dest->go[i]) dest = dest->go[i];
                next->fail = dest;
            
                }
                if(next->fail->end) next->end = 1;

            }

        }


    } 
    int Q;
    scanf("%d", &Q);
    for(int i=0; i<Q; i++){
        char temp[10010];
        scanf("%s", temp);
        int n = strlen(temp);
        yaho(root, temp, n);
    }

}