#include <stdio.h>
#include <string.h>


int arr[50][50];
int checked[50][50];
int baechu(int N, int M, int i, int j){

    checked[i][j]=1;
    int ans=1;
    if(j+1<M && arr[i][j+1]==1 && checked[i][j+1]!=1) ans+=baechu(N, M, i, j+1);
    if(i+1<N && arr[i+1][j]==1 && checked[i+1][j]!=1) ans+=baechu(N, M, i+1, j);
    if(j-1>=0 && arr[i][j-1]==1 && checked[i][j-1]!=1) ans+=baechu(N, M, i, j-1);
    if(i-1>=0 && arr[i-1][j]==1 && checked[i-1][j]!=1) ans+=baechu(N, M, i-1, j);

    return ans;
 }
int main(void){

    int n;

    scanf("%d", &n);
    while(n--){
        int M,N,K;
        int cnt=0;
        scanf("%d %d %d", &M, &N, &K);
        memset(arr, 0, sizeof(arr));
        memset(checked, 0, sizeof(checked));
        for(int i=0; i<K; i++){
            int a,b;
            scanf("%d %d", &a, &b);
            arr[a][b]=1;
        }
        for(int i=0; i<M; i++){
            for(int j=0; j<N; j++){
                if(arr[i][j] == 1 && checked[i][j]==0){
                    cnt++;
                    baechu(M, N, i, j);
                }

            }
        }
        printf("%d\n", cnt);
        
    }
}