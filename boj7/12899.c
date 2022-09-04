#include <stdio.h>
#include <string.h>

#define MAX 2000000

int logs(int N){
    if(N/2!=0) return 1+logs(N/2);
    else return 0;
}
void insert(int *tree, int node, int index, int start, int end){
    if(index<start || index> end) return;

    
    tree[node]++;
    if(start==end) return;
    int mid = (start+end)/2;
    insert(tree,node*2, index, start, mid);
    insert(tree,node*2+1, index, mid+1, end);
}

int erase(int *tree, int node, int order, int start, int end){
    
    tree[node]--;
    if(start==end){
        return start;
    }

    int mid = (start+end)/2;
    if(order<=tree[node*2]) return erase(tree, node*2, order, start, mid);
    else return erase(tree, node*2+1, order-tree[node*2], mid+1, end);
}
int main(void){

    int N;
    scanf("%d", &N);
    int h = logs(MAX)+1;
    
    int tree[1<<(h+1)];
    memset(tree, 0 ,sizeof(tree));
    for(int i=0; i<N; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        if(a==1){
            insert(tree, 1,b,1,MAX);
        }
        else if(a==2){
            printf("%d\n",erase(tree, 1, b, 1, MAX));
        }
    }
}