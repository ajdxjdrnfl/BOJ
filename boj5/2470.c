#include <stdio.h>
#include <stdlib.h>
#define INF 2000000001;
int arr[100000];
int left, right;
int comp(const void*a, const void*b){
    int pa = *(int*)a;
    int pb = *(int*)b;
    if(pa<pb) return -1;
    else if(pa>pb) return 1;
    return 0;
}

void solution(int N){

    int temp_l=0;
    int temp_r=N-1;
    int smallest= INF;
    while(temp_l<temp_r){
        
        int sum = arr[temp_l] + arr[temp_r];
        if(sum==0){
            left = temp_l;
            right = temp_r;
            return;
        }
        else if(sum>0){
            if(smallest>abs(sum)){
                smallest = abs(sum);
                left = temp_l;
                right = temp_r;
            }
            temp_r--;
            
        }
        else if(sum<0){
            if(smallest>abs(sum)){
                smallest = abs(sum);
                left = temp_l;
                right = temp_r;
            }
            temp_l++;
        }
    }
}

int main(void){
    int N;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, N, sizeof(int), comp);
    
    solution(N);
    printf("%d %d\n", arr[left], arr[right]);
}