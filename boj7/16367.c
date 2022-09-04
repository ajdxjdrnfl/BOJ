#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define B 0
#define R 1

typedef struct _NODE{
    struct _NODE *next;
    int num;
}NODE;
typedef struct _NODELIST{
    NODE *head;
}NODELIST;

void addEdge(NODELIST *list, int from, int to){
    NODE * node = list[from].head;
    NODE * pre = NULL;
    while(node!=NULL){
        if(node->num == to) return;
        else if(node->num > to) break; 
        else if(node->num < to){
            pre = node;
            node = node->next;
        }
    }
    NODE * new = (NODE*)malloc(sizeof(NODE));
    new->num = to;
    if(pre==NULL) {
        list[from].head = new;
        new->next = node;
    }
    else {
        new->next = node;
        pre->next = new;
    }
}
int d[20001];
int ssc[20001];
int stack[20001];
int top=0;
int id=0;
int ssc_num=0;

int alp(char a){
    if(a=='B') return B;
    else if(a=='R') return R;
}
void Insert(NODELIST *list,  int a, char b, int c, char d, int e, char f){
    if(b=='B'){
        addEdge(list, 2*a+R, 2*c+alp(d));
        addEdge(list, 2*a+R, 2*e+alp(f));
    }
    else{
        addEdge(list, 2*a+B, 2*c+alp(d));
        addEdge(list, 2*a+B, 2*e+alp(f));
    }
    if(d=='B'){
        addEdge(list, 2*c+R, 2*a+alp(b));
        addEdge(list, 2*c+R, 2*e+alp(f));
    }
    else{
        addEdge(list, 2*c+B, 2*a+alp(b));
        addEdge(list, 2*c+B, 2*e+alp(f));
    }
    if(f=='B'){
        addEdge(list, 2*e+R, 2*a+alp(b));
        addEdge(list, 2*e+R, 2*c+alp(d));
    }
    else{
        addEdge(list, 2*e+B, 2*a+alp(b));
        addEdge(list, 2*e+B, 2*c+alp(d));
    }
}
int min(int a, int b){
    return a<b?a:b;
}
int dfs(NODELIST *list, int index){
    d[index] = ++id;
    stack[top++] = index;

    int parent = d[index];
    NODE * temp = list[index].head;
    while(temp!=NULL){
       
        if(d[temp->num]==0) parent = min(parent, dfs(list, temp->num));
        else if(ssc[temp->num]==0) parent = min(parent, d[temp->num]);  
        temp = temp->next;
    }

    if(parent == d[index]){
        ssc_num++;
        while(1){
            int child = stack[--top];
            ssc[child] = ssc_num;
            if(child == index) break;
        }

    }
    return parent;
    
}
int main(void){
    int k,n;
    scanf("%d %d", &k, &n);
    NODELIST * list = (NODELIST*)malloc(sizeof(NODELIST)*(2*k+2));
    memset(d, 0, sizeof(d));
    memset(ssc, 0, sizeof(ssc));
    for(int i=0; i<n; i++){
        int a, c, e;
        char b,d,f;
        scanf("%d %c %d %c %d %c", &a, &b, &c, &d, &e, &f);
        Insert(list, a, b, c, d, e, f);
    }
    for(int i=2; i<=2*k+1; i++){
        if(d[i]==0) dfs(list, i);
    }
    for(int i=1; i<=k; i++){
        if(ssc[2*i+B] == ssc[2*i+R]) {
            printf("-1\n");
            break;
        }
        if(i==k){
             for(int i=1; i<=k; i++){
        if(ssc[2*i+B] < ssc[2*i+R]) printf("B");
        else printf("R");
    }
    printf("\n");
        }
    }
   
}