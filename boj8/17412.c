#include <stdio.h>
#include <string.h>


int flow[401][401];
int arr[401][401];
int size[401];
int visited[401];
int cap[401][401];
int main(void){

    int N,P;
    scanf("%d %d", &N, &P);
    memset(arr, 0, sizeof(arr));
    memset(size, 0, sizeof(size));
    memset(flow, 0, sizeof(flow));
    memset(visited, 0, sizeof(visited));
    
    for(int i=1; i<=P; i++){
        int a,b;
        scanf("%d %d", &a, &b);
        arr[a][size[a]++]  = b;
        arr[b][size[b]++] = a;
        cap[a][b] = 1;
    }
    
    int ans=0;
    
    while(1){
        int que[100001];
    int rear=0, front=0;
    que[front++] = 1;
    memset(visited, 0 ,sizeof(visited));
    while(rear<front){
        int temp = que[rear++];
        for(int i=0; i<size[temp]; i++){
            int index = arr[temp][i];
            
            if( !visited[index] && cap[temp][index]-flow[temp][index]>0) {
                visited[index] = temp;
                que[front++] = index;
                if(index==2){
                    ans++;
                    break;
                }
            }
        }

    }
    if(!visited[2]) break;
    for(int i=2; i!=1; i=visited[i]){
        flow[visited[i]][i]++;
        flow[i][visited[i]]--;
    }
    
    
    
    }
    printf("%d\n", ans);

}