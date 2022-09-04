#include <stdio.h>

int parent[201];
int root[201];
int plan[1001];

int findP(int index){
    while(parent[index]!=index){
        index = parent[index];
    }
    return index;
}

int checkSet(int a, int b){
    if(findP(a)==findP(b)) return 1;
    return 0;
}
int main(void){
    int N, M;
    scanf("%d", &N);
    scanf("%d", &M);
    

    
    for(int i=1; i<=N; i++){
        parent[i] = i;
        root[i] = 0;
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            int temp;
            scanf("%d", &temp);
            if(temp==1 && findP(i) != findP(j)){
                if(root[findP(i)] < root[findP(j)]) parent[findP(i)] = findP(j);
                else {
                    parent[findP(j)] = findP(i);
                    if(root[findP(i)]==root[findP(j)]) root[findP(i)] = root[findP(i)] + 1; 
                }
            } 
        }
    }
    for(int i=1; i<=M; i++){
        scanf("%d", &plan[i]);
    }
    int j = 2;
    while(j<=M){
        if(checkSet(plan[j-1], plan[j])==1) j++;
        else break;
    }
    if(j<=M) printf("NO\n");
    else printf("YES\n");
}