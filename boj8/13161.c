#include <stdio.h>
#include <string.h>

#define MAX 5000001

int pre[510];
int cap[510][510];
int flow[510][510];
int arr[510][100001];
int size[510];
int team[510];
int level[510];

int min(int a, int b){
    return a<b?a:b;
}
int leveling(int start, int end){
    memset(level, 0, sizeof(level));

    int que[100001];
    int rear=0, front=0;
    que[front++] = start;
    level[start] = 1;
    while(rear<front){
        int index = que[rear++];
        for(int i=0; i<size[index]; i++){
            int next = arr[index][i];
       
            if(!level[next] && cap[index][next] - flow[index][next] >0){
                level[next] = level[index] + 1;
                que[front++] = next;
            }
        }
    }
    return level[end];
}

int blocking(int index, int end, int c){
    

    if(index==end) return c;
   
    for(int i=pre[index]; i<size[index]; i++){
        pre[index] = i;
        int next = arr[index][i];
        if( level[next] && level[next] == level[index]+1 && cap[index][next] - flow[index][next] > 0){
            int temp = blocking(next,  end, min(c, cap[index][next]-flow[index][next]));
            if(temp>0){
                flow[index][next] += temp;
            flow[next][index] -= temp;
            return temp;
            }
        }
    }

    return 0;

    
}

int main(void){

    int N;
    int start = 501;
    int end = 502;
    scanf("%d", &N);
    memset(pre, 0 ,sizeof(pre));
    memset(size, 0, sizeof(size));
    memset(arr, 0, sizeof(arr));
    memset(flow,0 , sizeof(flow));
    memset(cap, 0, sizeof(cap));
    for(int i=1; i<=N; i++){
        scanf("%d", &team[i]);
        if(team[i]==1){
            cap[start][i] = 100000001;
            arr[start][size[start]++] = i;
            arr[i][size[i]++] = start; 
        }
        if(team[i]==2){
            cap[i][end] = 100000001;
            arr[i][size[i]++] = end; 
            arr[end][size[end]++] = i;
        }
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            
            scanf("%d", &cap[i][j]);
            if(i==j) continue;
            arr[i][size[i]++] = j; 
        }
    }

    
   
    
    
    
    int total=0;
    while(leveling(start, end)){
        memset(pre, 0 , sizeof(pre));
        while(1){
        int temp = blocking(start, end, MAX);
        if(temp==0) break;
        else total+=temp;
        }
    }
    printf("%d\n", total);
    
    memset(team,0, sizeof(team));
    int que[1000001];
    int rear=0, front=0;
    team[start] = 1;
    que[front++] = start;
    while(rear<front){
        int index = que[rear++];
        for(int i=0; i<size[index]; i++){
            int next = arr[index][i];
            if(!team[next] && cap[index][next] - flow[index][next]>0){
                team[next] = 1;
                que[front++] = next;
            }
        }
    }
    for(int i=1; i<=N; i++){
        if(team[i]==1) printf("%d ",i);
    }
    printf("\n");
    for(int i=1; i<=N; i++){
        if(team[i]!=1) printf("%d ", i);
    }
    printf("\n");
    


}