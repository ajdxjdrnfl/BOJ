#include <stdio.h>
#include <stdlib.h>

int cmp(const void*a, const void*b){

    int num1 = *(int*)a;
    int num2 = *(int*)b;

    if(num1 < num2) return -1;
    if(num1 > num2) return 1;
    return 0;
    }

int main(void){
    int N, temp, result = 0;
    scanf("%d", &N);
    int arr[N];
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }

    qsort(arr, N, sizeof(int), cmp);

    for(int i=0; i<N; i++){
        temp = 0;
        for(int j=0; j<=i; j++){
            temp+=arr[j];
        }
        result +=temp;
    }
    printf("%d\n", result);
}