#include <stdio.h>

int constructor(int target){
    int result;
    for(int i=1; i<target; i++){
        result = i;
        for(int j=i; j!=j/10; j=j/10){
            result += j%10;
        }
        if(result == target) return i;
    }

    return 0;

}


int main(void){
    int N;
    scanf("%d", &N);

    printf("%d", constructor(N));
}