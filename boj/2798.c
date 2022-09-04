#include <stdio.h>
#include <stdlib.h>


int blackjack(int *arr, int N,int M){
    int smallest=300001;
    for(int i=0; i<N-2; i++){
        for(int j=i+1; j<N-1; j++){
            for(int k=j+1; k<N; k++){
                
                if(M==arr[i]+arr[j]+arr[k]) return arr[i]+arr[j]+arr[k];
                else if(smallest>M-arr[i]-arr[j]-arr[k] && M>arr[i]+arr[j]+arr[k]) smallest = M- arr[i]-arr[j]-arr[k];

            }
        }
    }

    return M-smallest;

}

int main(void){
    int N,M;
    int *arr;
    scanf("%d %d\n",&N,&M);
    arr = malloc(sizeof(int)*N);
    for(int i=0; i<N; i++){
        scanf("%d", &arr[i]);
    }
    
    printf("%d",blackjack(arr,N,M));
}