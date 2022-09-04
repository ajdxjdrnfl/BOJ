#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int n;
int SA[200010];
int g[200010];
int tg[200010];
int RANK[200010];
int LCP[200010];
int t;

int comp(const void *a, const void*b){
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

void getSA(char * str){

    for(int i=0; i<n; i++){
        SA[i] = i;
        g[i] = str[i] - 'a';
    }
    t = 1;
    while(t<=n){
        g[n] = -1;
      
        qsort(SA, n, sizeof(int), comp);
        
        tg[SA[0]] = 0;
        for(int i=1; i<n; i++){
            
            if(cmp(SA[i-1], SA[i])){
                tg[SA[i]] = tg[SA[i-1]] +1;
            }
            else{
                tg[SA[i]] = tg[SA[i-1]];
            }
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
    int len=0;
    for(int i=0; i<n; i++){
        int k = RANK[i];
      
        if(k){

            int j = SA[k-1];
            while(str[j+len]==str[i+len]) {
                len++;
            
            }
            LCP[i] = len;
            if(len) len--;
        }
       
    }
}

int main(void){

    char str[200010];
    scanf("%d", &n);
    scanf("%s", str);

    getSA(str);
    
    getLCP(str);
 
    int ans=0;
   
    for(int i=0; i<n; i++){
        if(ans<LCP[i]) ans = LCP[i];
    }
    printf("%d\n", ans);
}