#include <stdio.h>
#define MAX 10001

int main(void){
    int num,N;
    int count[MAX]={0,};
    
    scanf("%d", &N);

    for(int i=0; i<N; i++){

        scanf("%d", &num);
        count[num]++;   
    }

    for(int i=0; i<MAX; i++){
        if(count[i]==0) continue;
        for(int j=0; j<count[i]; j++){
        printf("%d\n", i);
        }
    }

}