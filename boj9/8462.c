#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct _QUERY{
    int s,e,n;
}QUERY;

int arr[100001];
QUERY query[100001];
int sqrtN;
long long count[1000001];
long long result[100001];
int comQ(const void*a, const void*b){
    QUERY pa = *(QUERY*)a;
    QUERY pb = *(QUERY*)b;

    if(pa.s/sqrtN < pb.s/sqrtN) return -1;
    else if(pa.s/sqrtN > pb.s/sqrtN) return 1;
    else {
        if(pa.e<pb.e) return -1;
        else if(pa.e>pb.e) return 1;
        else return 0;
    }
}
int main(void){
    int n,t;
    scanf("%d %d", &n ,&t);
    for(int i=1; i<=n; i++){
        scanf("%d", &arr[i]);
    }
    sqrtN = sqrt(n);
    for(int i=1; i<=t; i++){
        scanf("%d %d", &query[i].s, &query[i].e);
        query[i].n = i;
    }
    qsort(query+1, t, sizeof(QUERY), comQ);
    memset(result, 0, sizeof(result));
    memset(count , 0, sizeof(count));
   
    int s=query[1].s, e = query[1].e;
    long long sum= 0;
    for(int i=s; i<=e; i++){
        sum -= count[arr[i]]*count[arr[i]]*arr[i];
        count[arr[i]]++;
        sum += count[arr[i]]*count[arr[i]]*arr[i];
    }
    result[query[1].n] = sum;

  
    for(int i=2; i<=t; i++){

        while(query[i].s < s){
            sum -= count[arr[--s]]*count[arr[s]]*arr[s];
            count[arr[s]]++;
            sum += count[arr[s]]*count[arr[s]]*arr[s];
        }
        while(query[i].s > s){
            sum -= count[arr[s]]*count[arr[s]]*arr[s];
            count[arr[s]]--;
            sum += count[arr[s]]*count[arr[s]]*arr[s++];
        }

        while(query[i].e < e){
            sum -= count[arr[e]]*count[arr[e]]*arr[e];
            count[arr[e]]--;
            sum += count[arr[e]]*count[arr[e]]*arr[e--];
        }
        while(query[i].e > e){
            sum -= count[arr[++e]]*count[arr[e]]*arr[e];
            count[arr[e]]++;
            sum += count[arr[e]]*count[arr[e]]*arr[e];
        }
        result[query[i].n] = sum;
    }
    for(int i=1; i<=t; i++){
        printf("%lld\n", result[i]);
    }
    
    

}