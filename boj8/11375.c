#include <stdio.h>
#include <string.h>

int arr[1001][1001];
int match[1001];
int size[1001];
int visited[1001];
int bipartie(int index, int N, int M){

    if(visited[index]!=0) return 0;

    visited[index] = 1;
    
    for(int i=1; i<=size[index]; i++){
        int temp = arr[index][i];
                if(!match[temp]){
                    match[temp] = index;
                    return 1;
                }
                else{
                    if(match[temp] != index && bipartie(match[temp], N, M)){
                        match[temp] = index;
                        return 1;
                    }
                    else{
                        continue;
                    }
                }
            
        
    }
    return 0;
    
}
int main(void){

    int N,M;
    scanf("%d %d", &N,&M);
    memset(arr, 0, sizeof(arr));
    memset(match, 0, sizeof(match));
    for(int i=1; i<=N; i++){
        int num;
        
        scanf("%d", &num);
        size[i] = num;
        for(int j=1; j<=num; j++){
            int temp;
            scanf("%d", &temp);
            arr[i][j] = temp;
        }
    }
    for(int i=1; i<=N; i++){
        memset(visited, 0 ,sizeof(visited));
        bipartie(i, N, M);
    }
    int cnt=0;
    for(int i=1; i<=M; i++){
        if(match[i]) {
            cnt++;
        
        }
    }
    printf("%d\n", cnt);
}