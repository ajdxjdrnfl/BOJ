#include <stdio.h>

int main(void){

    int N, K;
    int current;
    int result=0;
    int temp;
    scanf("%d %d", &N, &K);
    int arr[N];
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }
    current = N;
    temp = arr[current-1];
    while(1){
        
        if(K-temp>0){
            K -=temp;
            result++;
        }
        else if(K-temp<0){
            current--;
            temp = arr[current-1];
        }
        else{
            result++;
            break;
        }
    }
    printf("%d\n", result);
}