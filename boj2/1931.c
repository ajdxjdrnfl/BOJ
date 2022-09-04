#include <stdio.h>
#include <stdlib.h>

typedef struct _TIME{
    int start;
    int finish;
}TIME;


int cmp(const void*a, const void*b){

    TIME num1 = *(TIME*)a;
    TIME num2 = *(TIME*)b;

    if(num1.finish < num2.finish) return -1;

    if(num1.finish > num2.finish) return 1;

    if(num1.finish == num2. finish){
        if(num1.start < num2.start) return -1;
        if(num1.start > num2.start) return 1;
    }

    return 0;
}

int main(void){
    int N;
    int result=0;
    int pre;
    scanf("%d", &N);
    
    TIME time[N];
    for(int i=0; i<N; i++){
        scanf("%d %d", &time[i].start, &time[i].finish);
    }
    pre =0;
    
    qsort(time, N, sizeof(TIME),cmp);
    for(int i=0; i<N; i++){
        if(pre<=time[i].start){
            pre = time[i].finish;
            result++;
        }
    }
    
    printf("%d\n", result);

}