#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n,t;
int g[1000010];
int tg[1000010];
int RANK[1000010];
int SA[1000010];
int LCP[1000010];

int comp(const void*a, const void*b){
    int pa = *(int*)a;
    int pb = *(int*)b;

    int at = pa+t>=n?n:pa+t;
    int bt = pb+t>=n?n:pb+t;

    if(g[pa]==g[pb]) return g[at]<g[bt]?-1:1;
    else return g[pa]<g[pb]?-1:1;

}

int cmp(int a, int b){
    int at = a+t>=n?n:a+t;
    int bt = b+t>=n?n:b+t;

    if(g[a]==g[b]) return g[at]<g[bt];
    else return g[a]<g[b];
}
void getSA(char *str){

    
    for(int i=0; i<n; i++){
        SA[i] = i;
        g[i] = str[i]-'a';
    }

    t = 1;

    while(t<=n){

        g[n] = -1;
        qsort(SA, n, sizeof(int), comp);
        tg[SA[0]] = 0;

        for(int i=1; i<n; i++){
            
            if(cmp(SA[i-1], SA[i])) tg[SA[i]] = tg[SA[i-1]]+1;
            else tg[SA[i]]=tg[SA[i-1]];
        }

        for(int i=0; i<n; i++){
            g[i] = tg[i];
        }
        t *= 2;
        
    }
}

void getLCP(char *str){

    for(int i=0; i<n; i++){
        RANK[SA[i]] = i;
    }
    int len =0;
    for(int i=0; i<n; i++){
        int k = RANK[i];
        if(k){
            int x = SA[k-1];
            while(str[x+len]==str[i+len]) len++;
            LCP[i] = len;
            if(len) len--;
        }
    }

}
int main(void){

    char str[1000010];
    scanf("%s", str);
    n = strlen(str);
    getSA(str);
    getLCP(str);
    long long acc;
    long long temp = n;
    acc = (temp+1)*temp/2;
    for(int i=0; i<n; i++){
        acc -= LCP[i];
    }
    printf("%lld\n", acc);
}