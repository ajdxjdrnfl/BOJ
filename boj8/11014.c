#include <stdio.h>
#include <string.h>
int dx[6]={-1, 1, -1,1,-1,1};
int dy[6]={-1,-1,0,0,1,1};
int seat[81][81];
int visited[81][81];
int match[81][81];
int arr[81][81][81];
int size[81][81];

int bipartite(int i, int j, int N, int M){
    if(visited[i][j]) return 0;
    visited[i][j] = 1;
    
    for(int k=0; k<size[i][j]; k++){
        int temp = arr[i][j][k];
        int y = temp/81;
        int x = temp%81;

        if(!match[y][x]){
            match[y][x] = i*81+j;
            return 1;
        }
        else if(bipartite(match[y][x]/81, match[y][x]%81, N, M)){
            match[y][x] = i*81+j;
            return 1;
        }
    }
    return 0;
}
int main(void){

    int t;
    scanf("%d", &t);
    while(t--){
        int N,M;
        int all=0;
        int cnt=0;
        scanf("%d %d", &N, &M);
        memset(seat, 0, sizeof(seat));
        memset(visited, 0, sizeof(visited));
        memset(match, 0 ,sizeof(match));
        memset(arr, 0, sizeof(arr));
        memset(size, 0 , sizeof(size));
        for(int i=1; i<=N; i++){
            char s[100];
            scanf("%s", s);
            for(int j=1; j<=M; j++){
                if(s[j-1]=='.') {
                    seat[i][j] = 1;
                    all++;
                }
                else if(s[j-1]=='x') seat[i][j] = 0;
            }
        }

        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                for(int k=0; k<6; k++){

                    if(!seat[i][j]) break;
                    int x = j+dx[k];
                    int y = i+dy[k];
                    if(x<1 || x>M || y<1 || y>N) continue;
                    if(!seat[y][x]) continue;
                    arr[i][j][size[i][j]++] = y*81+x;                    
                }
            }
        }

        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j+=2){
                memset(visited, 0, sizeof(visited));
                if(bipartite(i,j,N,M)) cnt++;
            }
        }
        printf("%d\n", all-cnt);
        

    }
}