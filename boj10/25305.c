#include <stdio.h>
#include <stdlib.h>

int com(const void*a, const void*b){
    int pa = *(int*)a;
    int pb = *(int*)b;
    if(pa<pb) return 1;
    else return -1;
}
int main(void){

    int N,k;
    int num[1001];
    scanf("%d %d", &N, &k);
    for(int i=0; i<N; i++){
        scanf("%d", &num[i]);
    }
    qsort(num, N, sizeof(int), com);
    printf("%d\n", num[k-1]);
}
