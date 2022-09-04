#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct _QUERY{
    int s;
    int e;
    int n;
}QUERY;

int sqrtN;
int arr[100001];
int count[1000001];
QUERY query[100001];
int result[100001];

int comQ(const void*a, const void*b){
    QUERY pa = *(QUERY*)a;
    QUERY pb = *(QUERY*)b;
    if(pa.s/sqrtN < pb.s/sqrtN) return -1;
    else if(pa.s/sqrtN > pb.s/sqrtN) return 1; 
    else{
        if(pa.e<pb.e) return -1;
        else if(pa.e>pb.e) return 1;
        return 0;
    }
}

int mosAlgorithm(){

}

int main(void){

    int N, M;
    scanf("%d", &N);
    sqrtN = sqrt(N);
    for(int i=1; i<=N; i++){
        scanf("%d", &arr[i]);
    }
    scanf("%d", &M);
    for(int i=1; i<=M; i++){
        int a,b;
        scanf("%d %d", &query[i].s, &query[i].e);
        query[i].n = i;
    }
    qsort(query+1, M, sizeof(QUERY), comQ);
    memset(count , 0 ,sizeof(count));
    memset(result, 0 , sizeof(result));
    
    
    int s = query[1].s, e = query[1].e;
    int ans = 0;
    for(int i=s ; i<=e; i++){
        if(count[arr[i]]++==0) ans++;
    }
    result[query[1].n] = ans;

    for(int i=2; i<=M; i++){
       
        while(query[i].s<s) if(count[arr[--s]]++ == 0) ans++;
        while(query[i].s>s) if(--count[arr[s++]] == 0) ans--;

        while(query[i].e<e) if(--count[arr[e--]] == 0) ans--;
        while(query[i].e>e) if(count[arr[++e]]++==0) ans++;
        result[query[i].n] = ans;

    }   
    for(int i=1; i<=M; i++){
        printf("%d\n", result[i]);
    }
}