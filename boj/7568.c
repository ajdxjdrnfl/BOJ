#include <stdio.h>
#include <stdlib.h>

int mass(int *w, int *h, int index, int N){
    int result =1;
    for(int i=0; i<N; i++){

        if(i!=index && w[index]<w[i] && h[index] < h[i]) result++;
    }
    return result;

}

int main(void){

    int N;
    int *w;
    int *h;

    scanf("%d", &N);
    w = (int*)malloc(sizeof(int)*N);
    h = (int*)malloc(sizeof(int)*N);

    for(int i=0; i<N; i++){
        scanf("%d %d", &w[i], &h[i]);
    }

    for(int i=0; i<N; i++){ 
        printf("%d ", mass(w,h,i, N));
    }
}