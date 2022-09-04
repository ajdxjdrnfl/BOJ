#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int TEMP[26];
typedef struct _TRIE{
    struct _TRIE *go[4];
    struct _TRIE *fail;
    int end;
}TRIE;

TRIE * getTRIE(){

    TRIE *new = (TRIE*)malloc(sizeof(TRIE));
    for(int i=0; i<4; i++) new->go[i] = NULL;
    new->fail = NULL;    
    new->end = 0;
    return new;
}

void swap(char * a, char *b){
    char temp = *a;
    *a = *b;
    *b = temp;
}

void strrev(char *str, int i, int j){
    while(i<=j) swap(&str[i++], &str[j--]);
}

void insert(TRIE *root, char *str, int n){

    TRIE *temp = root;
    for(int i=0; i<n; i++){
        int index = TEMP[str[i]-'A'];
        if(!temp->go[index]) temp->go[index] = getTRIE();
        temp = temp->go[index];
    }
    temp->end = 1;
    
}

int yaho(TRIE *root, char* str, int n){

    int ans=0;
    TRIE * current = root;
    for(int i=0; i<n; i++){
        int index = TEMP[str[i] - 'A'];
        while(current != root && !current->go[index]) current = current->fail;
        if(current->go[index]) current = current->go[index];
        if(current->end) ans+=current->end;
    }
    return ans;
}

void freeTRIE(TRIE *root){
    for(int i=0; i<4; i++){
        if(root->go[i]) freeTRIE(root->go[i]);
    }
    free(root);
}
int main(void){

    int T;
    TEMP['A'-'A'] = 0;
    TEMP['G'-'A'] = 1;
    TEMP['T'-'A'] = 2;
    TEMP['C'-'A'] = 3;
    scanf("%d", &T);
    while(T--){

        int n,m;
        scanf("%d %d", &n, &m);
        char dna[1000010];
        char marker[110];
        scanf("%s", dna);
        scanf("%s", marker);
        TRIE * root = getTRIE();
        root->fail = root;
        
        insert(root, marker, m);
        for(int i=0; i<m; i++){
            for(int j=i+1; j<m; j++){
                strrev(marker, i, j);
                insert(root, marker, m);
                strrev(marker, i, j);
            }
        }
       
        TRIE* que[100000];
        int rear=0,front=0;
        que[front++] = root;
        while(rear<front){
            TRIE* temp = que[rear++];
            for(int i=0; i<4; i++){
                if(temp->go[i]){
                    TRIE *next = temp->go[i];
                    que[front++] = next;
                    if(temp==root) next->fail = root;
                    else{
                        TRIE *dest = temp->fail;
                        while(dest!=root && !dest->go[i]) dest = dest->fail;
                        if(dest->go[i]) dest = dest->go[i];
                         next->fail = dest;
                    }
                    if(next->fail->end) next->end += next->fail->end;
                

                }
            }
        }

        printf("%d\n", yaho(root, dna, n));
        freeTRIE(root);
    }
}