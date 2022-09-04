#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct _QUERY{
    int s,e,n;
}QUERY;

QUERY query[100001];
int arr[100001];
int sqrtN;
int result[100001];
int count[100001];
int ans_count[100001];

int comQ(const void*a, const void*b){
    QUERY pa = *(QUERY*)a;
    QUERY pb = *(QUERY*)b;

    if(pa.s/sqrtN < pb.s/sqrtN) return -1;
    else if(pa.s/sqrtN > pb.s/sqrtN) return 1;
    else{
        if(pa.e < pb.e) return -1;
        else if(pa.e > pb.e) return 1;
        else return 0;
    }
}

int max(int a, int b){
    return a>b?a:b;
}
int main(void){

    int N,M;
    scanf("%d", &N);
    for(int i=1; i<=N; i++){
        scanf("%d", &arr[i]);
    } 
    sqrtN = sqrt(N);

    scanf("%d", &M);
    for(int i=1; i<=M; i++){
        scanf("%d %d", &query[i].s, &query[i].e);
        query[i].n = i;
    }
    
    qsort(query+1, M, sizeof(QUERY), comQ);
    memset(result, 0 ,sizeof(result));
    memset(count, 0 , sizeof(count));
    memset(ans_count, 0 , sizeof(ans_count));

    int s = query[1].s, e = query[1].e;
    int lar=-1;
    for(int i=s; i<=e; i++){
        ++ans_count[++count[arr[i]]];
        lar = max(lar, count[arr[i]]);
    }
    result[query[1].n] = lar; 

    for(int i=2; i<=M+1; i++){
       
        while(query[i].s < s){
            ++ans_count[++count[arr[--s]]];
            lar = max(lar, count[arr[s]]);
        }
        while(query[i].s > s) {
            if(--ans_count[count[arr[s++]]--]==0 && lar == count[arr[s-1]]+1 ) lar--;
        }
        while(query[i].e < e){
            if(--ans_count[count[arr[e--]]--]==0 && lar == count[arr[e+1]]+1 ) lar--;
        }
        while(query[i].e > e){
            ++ans_count[++count[arr[++e]]];
            lar = max(lar, count[arr[e]]);
        }
        result[query[i].n] = lar;
        
    }
    for(int i=1; i<=M; i++){
        printf("%d\n", result[i]);
    }

    
}