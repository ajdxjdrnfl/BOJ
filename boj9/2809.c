#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int mark[300001];
int check[300001];
typedef struct _ELEMENT{
    int key;
    struct _TRIE *trie;
}element;

typedef struct _VEC{
    element *arr;
    int size;
    int last;
}VEC;

typedef struct _TRIE{
    VEC * vec;
    struct _TRIE *fail;
    int len;
    int end;
}TRIE;

void doubleVector(VEC *vec){

   vec->arr =(element*)realloc(vec->arr, sizeof(element)*2*vec->size);
   vec->size*=2;
}

TRIE* getTRIE(){
    TRIE *new =(TRIE*)malloc(sizeof(TRIE));

    new->vec = (VEC*)malloc(sizeof(VEC));
    new->vec->size=1;
    new->vec->last=-1;
    new->vec->arr = (element*)malloc(sizeof(element));
    new->vec->arr->trie = NULL;

    new->fail = NULL;
    new->end = 0;
    new->len = 0;

    return new;
}

void push_back(VEC * vec, int key){
    if(vec->last>=vec->size-1) doubleVector(vec);
    vec->arr[++vec->last].key = key;
    vec->arr[vec->last].trie = getTRIE();

}


TRIE * back(VEC * vec){
    return vec->arr[vec->last].trie;
}
TRIE * get(TRIE *root, int key){
    for(int i=0; i<=root->vec->last; i++){
        if(root->vec->arr[i].key == key) {
            return root->vec->arr[i].trie;
        } 
    }
    return NULL;
}
void input(TRIE *root, char *str, int n){
    
   
    TRIE * current = root;
    for(int i=0; i<n; i++){
        int index = str[i]-'a';
        TRIE * temp = get(current, index);
        
        if(temp) current = temp;
        else {
            push_back(current->vec, index);
            current = back(current->vec);   
        }

    }
    current->end = 1;
    current->len = n;
}

int max(int a, int b){
    return a>b?a:b;
}
int yaho(TRIE *root, char * str,int n){


    TRIE *current =root;
    
    for(int i=0; i<n; i++){
        int index = str[i]-'a';
        
        while(current!=root && !get(current, index)) {
            current = current->fail;
        }
        if(get(current , index)){
            current = get(current, index);
        }
        if(current->end) {
           mark[i] = current->len;
        }
        
    }   
    int ans = n;
    int last = -1;
    for(int i=0; i<n; i++){
        if(mark[i]){
            for(int j=i-mark[i]+1; j<=i; j++){
                if(!check[j]) {
                    ans--;
                    check[j] = 1;
                }
            }
        }
    }
    return ans;
}
int main(void){

    int N;
    scanf("%d", &N);
    char street[300010];
    scanf("%s", street);
    int M;
    scanf("%d", &M);

    TRIE * root = getTRIE(0);
    root->fail = root;
    memset(mark, 0, sizeof(mark));
    memset(check, 0 , sizeof(check));
    for(int i=0; i<M; i++){
        char temp[5010];
        scanf("%s", temp);
        input(root, temp, strlen(temp));
    }
    
    TRIE * que[50001];
    int rear=0,front=0;
    que[front++] = root;
    while(rear<front){
        TRIE * temp = que[rear++];
        for(int i=0; i<=temp->vec->last; i++){
            TRIE *next = temp->vec->arr[i].trie;
                que[front++] = next;
                int index = temp->vec->arr[i].key;
                if(temp==root) next->fail = root;
                else{
                    TRIE *dest = temp->fail;
                    while(dest!=root && !get(dest, index)) dest = dest->fail;
                    if(get(dest, index)) dest = get(dest, index);
                    next->fail = dest; 
                }
                if(next->fail->end) {
                    next->end += next->fail->end;
                    next->len = max(next->fail->len, next->len);
                }
            
        }
    }
   
    printf("%d\n", yaho(root, street, N));
}