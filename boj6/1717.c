#include <stdio.h>

int parent[1000001];
int root[1000001];

int findP(int index){
    while(parent[index]!=index){
        index = parent[index];
    }
    return index;
}

void checkSet(int a, int b){
    
    if(findP(a)==findP(b)) printf("YES\n");
    else printf("NO\n");
}
int main(void){
    int N,M;
    scanf("%d %d", &N, &M);
    for(int i=1; i<=N; i++){
        parent[i] = i;
        root[i] = 1;
    }
    for(int i=0; i<M; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if(a==0){
            int a_parent = findP(b);
            int b_parent = findP(c);
            if(root[a_parent] < root[b_parent]){
                parent[a_parent] = b_parent;
            }
            else{
                parent[b_parent] = a_parent;
                if(root[a_parent] == root[b_parent]) root[a_parent] = root[a_parent]+1;
            }
        } 
        else if(a==1) checkSet(b, c);
    }
}