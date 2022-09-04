#include <stdio.h>
#include <stdlib.h>
int **result;

int steps(int *arr, int N, int num, int height){
    if(num<0) return 0;
    if(result[height][num-1] !=0 )return result[height][num-1];

    int one, two;
    
    if(height == 1){
        result[height][num-1] = steps(arr, N, num-2, 0) + arr[num-1];
    }
    else if(height == 0){
        one = steps(arr, N, num-1, 1) + arr[num-1];
        two = steps(arr, N, num-2, 0) + arr[num-1];
        if(one<two) result[height][num-1] = two;
        else result[height][num-1]  = one;
        return result[height][num-1];
    }


    
}


int main(void){

    int N;
    int *arr;
    scanf("%d", &N);
    arr = (int*)malloc(sizeof(int)*N);
    result = (int **)malloc(sizeof(int*)*2);
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
        
    }
    for(int i=0; i<2; i++){
        result[i] = (int *)malloc(sizeof(int)*N);
    }

    steps(arr, N, N, 0);
    printf("%d\n", result[0][N-1]);

}