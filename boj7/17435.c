#include <stdio.h>


int parent[19][200001];

int comp(int n, int x){
    
    if(parent[n][x]!=0) return parent[n][x];

    parent[n][x] = comp(n-1, comp(n-1,x));
    return parent[n][x];
}

int main(void){

    int m,q;
    scanf("%d", &m);
    for(int i=1; i<=m; i++){
        scanf("%d", &parent[0][i]);
    }
    scanf("%d", &q);
    for(int i=0; i<q; i++){
        int n,x;
        scanf("%d %d", &n, &x);
        int j = 0;
        while(1){
            
            if(n==1){
                printf("%d\n", comp(j, x));
                break;
            }
        
            if(n%2==1) x = comp(j , x);
            n = n/2;
            j++;
            

        }
    }
    
}