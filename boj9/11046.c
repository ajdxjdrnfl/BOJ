#include <stdio.h>

int num[1000001];
int A[2000002];
int min(int a, int b){
    return a<b?a:b;
}
int manacher(int *arr, int len){
    
    int r=0, p=0;
    A[0] = 0;
    for(int i=1; i<len; i++){
        if(i<=r) A[i] = min(r-i, A[2*p-i]);
        else A[i] = 0; 
        
        while(i+A[i]+1<len && i-A[i]-1>=0 && arr[i+A[i]+1]==arr[i-A[i]-1]) A[i]++;
        
        if(r<i+A[i]){
            r = i+A[i];
            p = i;
        }
    }

}
int main(void){
    int N,M;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d", &num[i]);
    }
    int temp[2000002];
    for(int i=0; i<N; i++){
        temp[2*i+0] = 0;
        temp[2*i+1] = num[i];
    }
    temp[2*N] = 0;
    
    manacher(temp, 2*N+1);
    scanf("%d", &M);

    for(int i=0; i<M; i++){
        int S,E;
        scanf("%d %d", &S, &E);
        S = S-1, E = E-1;
        S = 2*S+1, E = 2*E+1;
        int mid = (S+E)/2;
        if(A[mid]+mid>=E && S>=A[mid]-mid) printf("1\n");
        else printf("0\n");
    }
}