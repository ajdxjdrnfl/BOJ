#include <stdio.h>

#define INF 40000001
int arr[401][401];

int min(int a, int b){
    return a<b?a:b;
}
void floyd(int V){
    for(int i=1; i<=V; i++){
        for(int j=1; j<=V; j++){
            for(int k=1; k<=V; k++){
                arr[j][k] = min(arr[j][k], arr[j][i] + arr[i][k]);
            }
        }
    }
}

int physics(int V){
    int shortest = INF;
    for(int i=1; i<=V; i++){
        for(int j=1; j<=V; j++){
            if(i==j) continue;
            shortest = min(shortest, arr[i][j] + arr[j][i]);
        }
    }
    return shortest;
}
int main(void){
    int V, E;
    scanf("%d %d", &V, &E);
        for(int j=1; j<=V; j++){
            for(int k=1; k<=V; k++){
                if(j==k) arr[j][k]=0;
                else arr[j][k] = INF;
            }
        }
    
    for(int i=0; i<E; i++){
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        arr[a][b] = c;
    }
    floyd(V);
    int result = physics(V);
    if(result>=INF) printf("-1\n");
    else printf("%d\n", result);
}