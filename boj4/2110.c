#include <stdio.h>
#include <stdlib.h>
int compare(const void*a, const void*b){
    int pa = *(int*)a;
    int pb = *(int*)b;

    if(pa<pb) return -1;
    else if(pa>pb) return 1;
    return 0;
}
int main(void){
    int N, C;
    int smallest, largest;
    scanf("%d %d", &N, &C);
    long long spot[N];
    int count=0;
    long long answer;
    for(int i=0; i<N; i++){
        scanf("%lld", &spot[i]);
    }
    qsort(spot, N, sizeof(long long), compare);
    
    long long low = 1;
    long long high = spot[N-1] - spot[0];
    
    while(low<=high){
        count=1;
        long long mid = (low+high)/2;
        int last = 0;

        for(int i=1; i<N; i++){
            if(spot[i]-spot[last]>=mid) {
                count++;
                last = i;
            }
        }

        if(count>=C){
            low = mid+1;
            answer = mid;
        }
        else high = mid-1;

        
    }
    printf("%lld\n", answer);
}