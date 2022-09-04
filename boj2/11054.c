#include <stdio.h>
#include <stdlib.h>

int main(void){
    
    int N, largest; 
    int arr[1001];
    int left[1001];
    int right[1001];
    scanf("%d", &N);

    left[1]=0;
    right[N]=0;
    for(int i=1; i<=N; i++){
        scanf("%d", &arr[i]);
    }

    for(int i=N-1; i>=1; i--){
        right[i] = 0;
        for(int j=i+1; j<=N; j++){
            if(arr[i]>arr[j]){
                if(right[i]<right[j]+1) right[i] = right[j] +1;
            } 
        }
    }

    for(int i=2; i<=N; i++){
        left[i] = 0;
        for(int j=i-1; j>=1; j--){
            if(arr[i]>arr[j]){
                if(left[i]<left[j] +1 ) left[i] = left[j] +1;
            }
        }
    }
    largest = right[1] + left[1];
    for(int i=2; i<=N; i++){
        if(largest< right[i] +left[i]) largest = right[i] + left[i];
    }
    printf("%d\n", largest+1);
}