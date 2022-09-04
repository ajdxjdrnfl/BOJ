#include <stdio.h>
#include <string.h>

int arr[501][501];
int match[501];
int visited[501];
int size[501];

int bipartite(int index, int n){
    if(visited[index]) return 0;
    visited[index]=1;
    for(int i=0; i<size[index]; i++){
        int temp = arr[index][i];
        if(!match[temp]){
            match[temp] = index;
            return 1;
        }

        else if(bipartite(match[temp], n)){
            match[temp] = index;
            return 1;
        }

    }
    return 0;
}
int main(void){

    int n,k;
    scanf("%d %d", &n, &k);
    memset(arr, 0, sizeof(arr));
    memset(size, 0 ,sizeof(size));

    for(int i=1; i<=k; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        arr[a][size[a]++] = b;
    }

    memset(match, 0 , sizeof(match));
    int cnt=0;
    for(int i=1; i<=n; i++){
        memset(visited, 0, sizeof(visited));
        if(bipartite(i,n)) cnt++;
    }
    printf("%d\n", cnt);
}