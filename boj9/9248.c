#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int g[500010];
int tg[500010];
int SA[500010];
int LCP[500010];
int RANK[500010];
int t,n;
int cmp(const void*a, const void*b){

    int pa = *(int*)a;
    int pb = *(int*)b;

    int at = pa+t;
    int bt = pb+t;

    if(pa+t>=n) at = n;
    if(pb+t>=n) bt = n;
    if(g[pa]==g[pb]){
        return g[at]<g[bt]?-1:1;
    }
    else{
        return g[pa]<g[pb]?-1:1;
    }
}

int comp(int a, int b){
    if(g[a]==g[b]) return g[a+t]<g[b+t];
    else return g[a]<g[b];
}

void getLCP(char *str){

    int len=0;
    int n = strlen(str);
    for(int i=0; i<n; i++){
        RANK[SA[i]] = i;
    }

    for(int i=0; i<n; i++){

        int k = RANK[i];

        if(k){
            
            int j = SA[k-1];
            
            while(str[j+len] == str[i+ len]) len++;

            LCP[k] = len;
            if(len) len--;
        }
    }
}

void getSA(char *str){
    n = strlen(str);
    t = 1;
    for(int i=0; i<n; i++){
        SA[i] = i;
        g[i] = str[i] - 'a';
    }

   
    while(t<=n){
        g[n] = -1;
        qsort(SA, n, sizeof(int), cmp);
        tg[SA[0]]=0;

        for(int i=1; i<n; i++){
            if(comp(SA[i-1], SA[i]))    tg[SA[i]] = tg[SA[i-1]]+1;
            else tg[SA[i]] = tg[SA[i-1]];
        }

        for(int i=0; i<n; i++){
            g[i] = tg[i];
        }
        t*=2;
    }
}
int main(void){

    char str[500010];
    scanf("%s", str);
    getSA(str);
    for(int i=0; i<n; i++){
        printf("%d ", SA[i]+1);
    }
    printf("\n");
    getLCP(str);
    printf("x ");
    for(int i=1; i<n; i++){
        printf("%d ", LCP[i]);
    }
    printf("\n");
}