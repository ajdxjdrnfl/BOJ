#include <stdio.h>
#include <stdlib.h>

int cmp(const void*a, const void*b){
    int pa = *(int*)a;
    int pb = *(int*)b;
    if(pa<pb) return -1;
    if(pa>pb) return 1;
    return 0;
}

#define MAX 360000

int A[MAX*2];
int B[MAX];
int kmp[MAX];
void preprocess(int size){
    int j =0;
    kmp[0] = 0;
    for(int i=1; i<size; i++){
        while(j>0 && B[i]!=B[j]){
            j = kmp[j-1];
        }

        if(B[i]==B[j]){
            j++;
            kmp[i] = j;
        }
    }
}

void clock(int n, int m){
    int j=0;
    for(int i=0; i<n; i++){
        while(j>0 && A[i]!=B[j]){
            j = kmp[j-1];
        }

        if(A[i]==B[j]){
            if(j==m-1){
                printf("possible\n");
                return;
            }
            else j++;
        }
    }
    printf("impossible\n");
    return ;
}

int main(void){

    int n;
    scanf("%d", &n);
    int a[n];
    int b[n];

    for(int i=0; i<n; i++){
        scanf("%d", &a[i]);        
    }
    for(int i=0; i<n; i++){
        scanf("%d", &b[i]);
    }
    qsort(a, n, sizeof(int), cmp);
    qsort(b, n, sizeof(int), cmp);
    for(int i=1; i<n; i++){
        A[i-1] = a[i] - a[i-1];
        A[n+(i-1)] = a[i] - a[i-1];
        B[i-1] = b[i] - b[i-1]; 
    }
    A[n-1] = (a[0] - a[n-1]+MAX)%MAX;
    preprocess(n-1);

    clock(2*n-1, n-1);

}