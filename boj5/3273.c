#include <stdio.h>
#include <stdlib.h>


int arr[1000001];
int comp(const void*a, const void*b){
    int pa = *(int *)a;
    int pb = *(int *)b;

    if(pa<pb) return -1;
    else if(pa>pb) return 1;
    return 0;
}

int two_pointer(int n, int x){
    int result=0;
    int left=0, right= n-1;
    while(left!=right){
        if(arr[left] + arr[right] == x){
            result++;
            left++;
            right--;
        }
        else if(arr[left]+arr[right]<x) left++;
        else right--;
    }
    return result;
}
int main(void){
    int n,x;
    int result;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, n, sizeof(int), comp);
    scanf("%d", &x);
    result = two_pointer(n,x);
    printf("%d\n", result);
}