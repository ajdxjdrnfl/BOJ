#include <stdio.h>


void sort(int *arr, int *brr, int N){
    int temp, temp_b;
    for(int i=1; i<N; i++){
        temp = arr[i];
        temp_b = brr[i];
        for(int j=i-1; j>=0; j--){
            if(temp>arr[j]){
                arr[j+1] = temp;
                brr[j+1] = temp_b;
                break;
            }
            else{
                arr[j+1] = arr[j];
                brr[j+1] = brr[j];
            }
            if(j==0){
                arr[j] = temp;
                brr[j] = temp_b;
            }
        }
    }
}
int main(void){

    int N, largest, temp;
    int arr[1001], brr[1001];
    int dp[1001];
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
        scanf("%d", &brr[i]);
    }
    sort(arr, brr, N);
    dp[N-1] = 1;
    for(int i=N-2; i>=0; i--){
        dp[i] = 1;
        for(int j=i+1; j<N; j++){
            if(brr[i] < brr[j]){
                if(dp[i] < dp[j] +1 ) dp[i] = dp[j]+1;
            }
        }
    }
    
    largest = dp[0];
    for(int i=1; i<N; i++){
        if(largest < dp[i]) largest = dp[i];
    }
    
    printf("%d\n",  N-largest);

}