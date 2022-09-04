#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int arr[51];
int match[51];
int visited[51];

int comp(const void*a, const void*b){
    int pa = *(int*)a;
    int pb = *(int*)b;
    if(pa<pb) return -1;
    if(pa>pb) return 1;
    return 0;
}
int prime(int N){

    if(N==2) return 1;
    if(N==3) return 1;
    for(int i=2; i<=(int)sqrt(N)+1; i++){
        if(N%i==0) return 0;
    }
    return 1;
}

int bipartie(int index, int N){

    if(visited[index]) return 0;

    visited[index] = 1;
    for(int i=2; i<=N; i++){
        if(prime(arr[i]+arr[index])){
            if(!match[i] && !visited[i]){
                match[i] = index;
                match[index] = i;
                return 1;
            } 
            else if( match[i] && bipartie(match[i], N)){
                match[i] = index;
                match[index] = i;
                return 1;
            }
        }
    }
    
    return 0;
}
int main(void){
    int N;
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        scanf("%d", &arr[i]);
    }
    int cnt=0;
    int ans[51];
    int size=0;
    for(int i=2; i<=N; i++){
        
        if(prime(arr[i]+arr[1])){
            cnt = 0;
            memset(match, 0, sizeof(match));
            match[i] = 1;
            match[1] = i;
            cnt++;
            for(int j=2; j<=N; j++){
                if(arr[j]%2==0 && !match[j]) {
                    memset(visited, 0, sizeof(visited));
                    visited[i] = 1;
                    visited[1] = 1;     
                    if(bipartie(j, N)) cnt++;
                }
            }
            
            if(cnt*2==N) ans[size++] = arr[i];
            
            
        }
        
    }
    if(size==0) printf("-1\n");
    else{
        qsort(ans, size, sizeof(int), comp);
        for(int i=0; i<size; i++){
            printf("%d ", ans[i]);
        }
        printf("\n");
    }   
}